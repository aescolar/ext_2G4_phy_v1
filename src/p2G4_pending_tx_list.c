/*
 * Copyright 2018 Oticon A/S
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <stdlib.h>
#include <string.h>
#include "bs_pc_2G4_types.h"
#include "bs_oswrap.h"
#include "bs_utils.h"
#include "p2G4_pending_tx_rx_list.h"

tx_l_c_t tx_l_c;
static tx_el_t *tx_list = NULL;

static uint nbr_devs;
static int max_tx_nbr; //highest device transmitting at this point

void txl_create(uint n_devs){
  tx_l_c.tx_list = bs_calloc(n_devs, sizeof(tx_el_t));
  tx_l_c.used = bs_calloc(n_devs, sizeof(uint));
  tx_l_c.ctr = 0;
  tx_list = tx_l_c.tx_list;
  nbr_devs = n_devs;
  max_tx_nbr = -1;
}

void txl_free(void){
  if ( tx_l_c.tx_list != NULL ) {
    for (int d = 0 ; d < nbr_devs; d++){
      if ( tx_list[d].packet != NULL ) {
        free(tx_list[d].packet);
      }
    }
    free(tx_l_c.tx_list);
    free(tx_l_c.used);
  }
}

/**
 * Register a tx which has just been initiated by a device
 * Note that the tx itself does not start yet (when that happens txl_activate() should be called)
 */
void txl_register(uint d, p2G4_tx_t *tx_s, uint8_t* packet){
  tx_l_c.used[d] = 0;
  memcpy(&(tx_list[d].tx_s), tx_s, sizeof(p2G4_tx_t) );
  tx_list[d].packet = packet;
}

/**
 * Activate a given tx in the tx_list_c (we have reached the begining of the Tx)
 */
void txl_activate(uint d){
  tx_l_c.used[d] = 1;
  tx_l_c.ctr++;
  max_tx_nbr = BS_MAX(max_tx_nbr, ((int)d));
}

/**
 * A given tx has just ended
 */
void txl_clear(uint d){
  tx_l_c.used[d] = 0;
  if (tx_list[d].packet != NULL) {
    free(tx_list[d].packet);
    tx_list[d].packet = NULL;
  }
  tx_l_c.ctr++;

  for (int i = max_tx_nbr; i >= 0 ; i--){
    if (tx_l_c.used[i]){
      max_tx_nbr = i;
      return;
    }
  }
  max_tx_nbr = -1;//if we didnt find any
}

/**
 * Find if there is a fitting tx for this rx attempt
 * if there is not, return -1
 * if there is, return the device number
 */
int txl_find_fitting_tx(p2G4_rx_t *rx_s, bs_time_t current_time){
  register uint *used = tx_l_c.used;
  for (int i = 0 ; i <= max_tx_nbr; i++) {
    if ((used[i]) &&
       (tx_list[i].tx_s.start_time == current_time) &&
       (tx_list[i].tx_s.phy_address == rx_s->phy_address) &&
       (tx_list[i].tx_s.radio_params.center_freq == rx_s->radio_params.center_freq) &&
       ((tx_list[i].tx_s.radio_params.modulation & P2G4_MOD_SIMILAR_MASK) ==
           (rx_s->radio_params.modulation & P2G4_MOD_SIMILAR_MASK)))
    {
      return i;
    }
  }
  return -1;
}
