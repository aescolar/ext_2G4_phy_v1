/*
 * Copyright 2023 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <string.h>

#include "bs_pc_2G4_types.h"
#include "bs_pc_2G4_utils.h"

void map_radioparamsv1_to_v2(p2G4_radioparamsv2_t *v2, p2G4_radioparams_t *v1) {
  v2->modulation = v1->modulation;
  v2->center_freq = p2G4_freq_to_freq2(v1->center_freq);
}

void map_rxv2_resp_to_rxv1(p2G4_rx_done_t *rx_done_v1, p2G4_rxv2_done_t *rx_done_v2){
  rx_done_v1->end_time = rx_done_v2->end_time;
  rx_done_v1->packet_size = rx_done_v2->packet_size;
  memcpy(&rx_done_v1->rssi, &rx_done_v2->rssi, sizeof(p2G4_rssi_done_t));
  rx_done_v1->rx_time_stamp = rx_done_v2->rx_time_stamp;
  rx_done_v1->status = rx_done_v2->status;
}

void map_rxv1_to_rx2v1(p2G4_rx2v1_t *rx_2v1_s, p2G4_rx_t *rx_v1_s) {
  rx_2v1_s->start_time    = rx_v1_s->start_time;
  rx_2v1_s->scan_duration = rx_v1_s->scan_duration;
  rx_2v1_s->error_calc_rate = rx_v1_s->bps;
  rx_2v1_s->antenna_gain  = rx_v1_s->antenna_gain;
  rx_2v1_s->pream_and_addr_duration  = rx_v1_s->pream_and_addr_duration;
  rx_2v1_s->header_duration  = rx_v1_s->header_duration;
  rx_2v1_s->acceptable_pre_truncation = 0;
  rx_2v1_s->sync_threshold = rx_v1_s->sync_threshold;
  rx_2v1_s->header_threshold = rx_v1_s->header_threshold;
  rx_2v1_s->resp_type = 0;
  rx_2v1_s->n_addr = 1;
  rx_2v1_s->prelocked_tx = 0;
  rx_2v1_s->coding_rate = 0;
  rx_2v1_s->forced_packet_duration = UINT32_MAX;
  map_radioparamsv1_to_v2(&rx_2v1_s->radio_params, &rx_v1_s->radio_params);
  memcpy(&rx_2v1_s->abort, &rx_v1_s->abort, sizeof(p2G4_abort_t));
}

void map_rxv2_to_rx2v1(p2G4_rx2v1_t *rx_2v1_s, p2G4_rxv2_t *rx_v2_s) {
  rx_2v1_s->start_time    = rx_v2_s->start_time;
  memcpy(&rx_2v1_s->abort, &rx_v2_s->abort, sizeof(p2G4_abort_t));
  rx_2v1_s->scan_duration = rx_v2_s->scan_duration;
  rx_2v1_s->forced_packet_duration = rx_v2_s->forced_packet_duration;
  rx_2v1_s->error_calc_rate = rx_v2_s->error_calc_rate;
  map_radioparamsv1_to_v2(&rx_2v1_s->radio_params, &rx_v2_s->radio_params);
  rx_2v1_s->antenna_gain  = rx_v2_s->antenna_gain;
  rx_2v1_s->coding_rate = rx_v2_s->coding_rate;
  rx_2v1_s->pream_and_addr_duration  = rx_v2_s->pream_and_addr_duration;
  rx_2v1_s->header_duration  = rx_v2_s->header_duration;
  rx_2v1_s->acceptable_pre_truncation = rx_v2_s->acceptable_pre_truncation;
  rx_2v1_s->sync_threshold = rx_v2_s->sync_threshold;
  rx_2v1_s->header_threshold = rx_v2_s->header_threshold;
  rx_2v1_s->prelocked_tx = rx_v2_s->prelocked_tx ;
  rx_2v1_s->resp_type = rx_v2_s->resp_type;
  rx_2v1_s->n_addr = rx_v2_s->n_addr;
}

void map_txv1_to_tx2v1(p2G4_tx2v1_t *tx_2v1_s, p2G4_tx_t *tx_v1_s) {
  tx_2v1_s->start_tx_time = tx_v1_s->start_time;
  tx_2v1_s->end_tx_time = tx_v1_s->end_time;
  tx_2v1_s->start_packet_time = tx_v1_s->start_time;
  tx_2v1_s->end_packet_time = tx_v1_s->end_time;
  tx_2v1_s->phy_address = tx_v1_s->phy_address;
  memcpy(&tx_2v1_s->abort, &tx_v1_s->abort, sizeof(p2G4_abort_t));
  map_radioparamsv1_to_v2(&tx_2v1_s->radio_params, &tx_v1_s->radio_params);
  tx_2v1_s->power_level = tx_v1_s->power_level;
  tx_2v1_s->coding_rate = 0;
  tx_2v1_s->packet_size = tx_v1_s->packet_size;
}

void map_txv2_to_tx2v1(p2G4_tx2v1_t *tx_2v1_s, p2G4_txv2_t *tx_v2_s) {
  tx_2v1_s->start_tx_time = tx_v2_s->start_tx_time;
  tx_2v1_s->end_tx_time = tx_v2_s->end_tx_time;
  tx_2v1_s->start_packet_time = tx_v2_s->start_packet_time;
  tx_2v1_s->end_packet_time = tx_v2_s->end_packet_time;
  tx_2v1_s->phy_address = tx_v2_s->phy_address;
  memcpy(&tx_2v1_s->abort, &tx_v2_s->abort, sizeof(p2G4_abort_t));
  map_radioparamsv1_to_v2(&tx_2v1_s->radio_params, &tx_v2_s->radio_params);
  tx_2v1_s->power_level = tx_v2_s->power_level;
  tx_2v1_s->coding_rate = tx_v2_s->coding_rate;
  tx_2v1_s->packet_size = tx_v2_s->packet_size;
}

void map_rssiv1_to_rssiv2(p2G4_rssiv2_t *RSSIv2_s, p2G4_rssi_t *RSSI_s) {
  RSSIv2_s->meas_time = RSSI_s->meas_time;
  map_radioparamsv1_to_v2(&RSSIv2_s->radio_params, &RSSI_s->radio_params);
  RSSIv2_s->antenna_gain = RSSI_s->antenna_gain;
}

void map_ccav1_to_ccav2(p2G4_ccav2_t *CCAv2_s, p2G4_cca_t *CCA_s) {
  CCAv2_s->start_time = CCA_s->start_time;
  memcpy(&CCAv2_s->abort, &CCA_s->abort, sizeof(p2G4_abort_t));
  CCAv2_s->scan_duration = CCA_s->scan_duration;
  CCAv2_s->scan_period = CCA_s->scan_period;
  map_radioparamsv1_to_v2(&CCAv2_s->radio_params, &CCA_s->radio_params);
  CCAv2_s->mod_threshold = CCA_s->mod_threshold;
  CCAv2_s->rssi_threshold = CCA_s->rssi_threshold;
  CCAv2_s->antenna_gain = CCA_s->antenna_gain;
  CCAv2_s->stop_when_found = CCA_s->stop_when_found;
}
