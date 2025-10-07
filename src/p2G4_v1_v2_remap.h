/*
 * Copyright 2023 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef P2G4_V1_V2_REMAP_H
#define P2G4_V1_V2_REMAP_H

#include "bs_types.h"
#include "bs_cmd_line_typical.h"
#include "bs_pc_2G4_types.h"

#ifdef __cplusplus
extern "C" {
#endif

void map_rxv2_resp_to_rxv1(p2G4_rx_done_t *rx_done_v1, p2G4_rxv2_done_t *rx_done_v2);
void map_rxv1_to_rx2v1(p2G4_rx2v1_t *rx_v2_s, p2G4_rx_t *rx_v1_s);
void map_rxv2_to_rx2v1(p2G4_rx2v1_t *rx_2v1_s, p2G4_rxv2_t *rx_v2_s);
void map_txv1_to_tx2v1(p2G4_tx2v1_t *tx_v2_s, p2G4_tx_t *tx_v1_s);
void map_txv2_to_tx2v1(p2G4_tx2v1_t *tx_2v1_s, p2G4_txv2_t *tx_v2_s);
void map_rssiv1_to_rssiv2(p2G4_rssiv2_t *RSSIv2_s, p2G4_rssi_t *RSSI_s);
void map_ccav1_to_ccav2(p2G4_ccav2_t *CCAv2_s, p2G4_cca_t *CCA_s);

#ifdef __cplusplus
}
#endif

#endif
