/** @file eqep.c 
*   @brief EQEP Driver Source File
*   @date 25.July.2013
*   @version 03.06.00
*
*   This file contains:
*   - API Functions
*   - Interrupt Handlers
*   .
*   which are relevant for the EQEP driver.
*/

/* (c) Texas Instruments 2009-2013, All rights reserved. */


#include "eqep.h"

/*the functions
*/

/* USER CODE BEGIN (0) */
/* USER CODE END */

/** @fn void QEPInit(void)
*   @brief Initializes the eQEP Driver
*
*   This function initializes the eQEP module.
*/
void QEPInit(void)
{

/* USER CODE BEGIN (1) */
/* USER CODE END */

  /** - Clear Position Counter register   */
  eqepREG1->QPOSCNT  =  0x00000000U;
  
  /** - Initialize Position Counter value register   */ 
  eqepREG1->QPOSINIT =  0x00000000U;
  
  /** - Set Maximum position counter value   */ 
  eqepREG1->QPOSMAX  =  0x00000000U;
  
  /** - Set the initiaa Position compare value   */ 
  eqepREG1->QPOSCMP  =  0x00000000U;
  
  /** - Clear the time base   */ 
  eqepREG1->QUTMR    =  0x00000000U;
  
  /** - Configure unit period register   */ 
  eqepREG1->QUPRD    =  (uint16) 0x00000000U;
  
  /** - Clear Watchdog Timer register  */ 
  eqepREG1->QWDTMR   = 	(uint16) 0x00000000U;
  
  /** - Configure Watchdog Period   */ 
  eqepREG1->QWDPRD   =  (uint16) 0x0000U;
  
/* USER CODE BEGIN (2) */
/* USER CODE END */

  /** - Setup Decoder Control Register
  *     - Select Position counter Mode
  *     - Enable / Disable Sync Output
  *     - Select Sync Output Pin  
  *     - Select external Clock rate ( resolution)
  *     - Enable / Disable Swap Quadrature clock input
  *     - Enable / Disable Gating of index pulse with Strobe.
  *     - Enable / Disable Negate QEPA input
  *     - Enable / Disable Negate QEPB input
  *     - Enable / Disable Negate QEPI input
  *     - Enable / Disable Negate QEPS input  
  */
  eqepREG1->QDECCTL  = (uint16)((QEP_DIRECTION_COUNT << 14U)
                       | (0U << 13U) 
					   | (QEP_INDEX_PIN << 12U) 
					   | (QEP_RESOLUTION_1x << 11U)
					   | (0U << 10U)
					   | (0U << 9U)
					   | (0U << 8U)
					   | (0U << 7U)					   
					   | (0U << 6U)				   
					   | (0U << 5U)
					   | 0x0000U);

  /** - Setup eQEP Control Register
  *     - Select Position counter Reset Mode
  *     - Enable & Select Stobe event initialization of position counter
  *     - Enable & Select Index event initialization of position counter
  *     - Enable / Disable Software Initialization of Position counter.
  *     - Select Strobe event latch of position counter.
  *     - Select Index event latch of position counter.
  *     - Select EQEP capture Latch mode
  */				   
  eqepREG1->QEPCTL   = (uint16)((QEP_MAX_POSITION << 12U)
                       | (0U << 11U )
					   | (QEP_DIRECTON_DEPENDENT << 10U)
                       | (0U << 9U)
					   | (QEP_RISING_EDGE << 8U)
					   | (0U << 7U)
					   | (QEP_RISING_EDGE << 6U)
					   | (QEP_LATCH_RISING_EDGE << 4U)
					   | (QEP_ON_POSITION_COUNTER_READ << 2U)
					   | 0x0000U);
					   
  /** - Setup eQEP Position Control Register
  *     - Enable / Disable Position compare shadow.
  *     - Select Position compare shadow load mode.
  *     - Select Polarity of Sync output.
  *     - Select Position compare sync output pulse width.
  */			   
  eqepREG1->QPOSCTL  = (uint16)((0U << 15U)
					   | (QEP_QPOSCNT_EQ_QPSCMP << 14U)
					   | (QEP_ACTIVE_HIGH << 13U)
					   | (0x000U)					   
					   | 0x0000U);

  /** - Setup eQEP Capture Control Register
  *     - Select capture timer clock prescaler.
  *     - Select Unit position event prescaler.
  */					   
  eqepREG1->QCAPCTL  = (uint16)((QEP_PS_8 << 4U)
					   | (QEP_PS_512)
					   | 0x0000U);

/* USER CODE BEGIN (3) */
/* USER CODE END */

  /** - Clear Interrupt Flag register  */					   
  eqepREG1->QCLR     = (uint16) 0xFFFFU;

  /** - Setup eQEP Interrupt Enable Register
  *     Enable / Diable UTO Interrupt
  *     Enable / Diable IEL Interrupt
  *     Enable / Diable SEL Interrupt
  *     Enable / Diable PCM Interrupt 
  *     Enable / Diable PCR Interrupt
  *     Enable / Diable PCO Interrupt
  *     Enable / Diable PCU Interrupt
  *     Enable / Diable WTO Interrupt 
  *     Enable / Diable QDC Interrupt
  *     Enable / Diable QPE Interrupt
  *     Enable / Diable PCE Interrupt
  */  
  eqepREG1->QEINT    = (uint16)((0U << 11U)
					   | (0U << 10U)
					   | (0U << 9U)
					   | (0U << 8U)
					   | (0U << 7U)
					   | (0U << 6U)
					   | (0U << 5U)
					   | (0U << 4U)
					   | (0U << 3U)       
					   | (0U << 2U)
					   | (0U << 1U));

  /** - Clear Capture Timer register  */
  eqepREG1->QCTMR    = (uint16)0x0000U;	

  /** - Clear the Capture Period regiter */  
  eqepREG1->QCPRD    = (uint16)0x0000U;	
  
  /** - Clear Period Latch register */					   
  eqepREG1->QCPRDLAT = (uint16)0x0000U;
  
/* USER CODE BEGIN (4) */
/* USER CODE END */
  
}

void QEP_clear_all_interrupt_flags (eqepBASE_t *eqep)
{
  
  eqep->QCLR = 0xfffU;
  
  return;	
} /*end of QEP_clear_all_interrupt_flags() function */

void QEP_clear_interrupt_flag (eqepBASE_t *eqep, const QEINT_t QEINT)
{
  
  eqep->QCLR |= QEINT;
  
  return;	
} /*end of QEP_clear_interrupt_flag() function */

void QEP_clear_posn_counter (eqepBASE_t *eqep)
{
  
  eqep->QPOSCNT = 0U;	
  
  return;
} /*end of QEP_clear_posn_counter() function */

void QEP_disable_all_interrupts (eqepBASE_t *eqep)
{
  
  eqep->QEINT = 0U;
  
  return;
} /*end of QEP_disable_all_interrupts () function */

void QEP_disable_capture (eqepBASE_t *eqep)
{
  
  eqep->QCAPCTL &= (~QEP_QCAPCTL_CEN);
  
  return;	
} /*end of QEP_disable_capture () function */

void QEP_disable_gate_index (eqepBASE_t *eqep)
{
  
  eqep->QDECCTL &= (~QEP_QDECCTL_IGATE);	
  
  return;
} /*end of QEP_disable_gate_index () function */

void QEP_disable_interrupt (eqepBASE_t *eqep, const QEINT_t QEINT)
{
  
  eqep->QEINT &= (~QEINT);
  
  return;
} /*end of QEP_disable_interrupt */

void QEP_disable_posn_compare (eqepBASE_t *eqep)
{
  
  eqep->QPOSCTL &= (~QEP_QPOSCTL_PCE);
  
  return;	
} /*end of QEP_disable_posn_compare () function */

void QEP_disable_posn_compare_shadow (eqepBASE_t *eqep)
{
  
  eqep->QPOSCTL &= (~QEP_QPOSCTL_PCSHDW);
  
  return;	
} /*end of QEP_disable_posn_compare_shadow () function */

void QEP_disable_sync_out (eqepBASE_t *eqep)
{
  
  eqep->QDECCTL &= (~QEP_QDECCTL_SOEN);
  
  return;
} /*end of QEP_disable_sync_out () function */

void QEP_disable_unit_timer (eqepBASE_t *eqep)
{
  
  eqep->QEPCTL &= (~QEP_QEPCTL_UTE);
  
  return; 	
} /*end of QEP_disable_unit_timer () function */

void QEP_disable_watchdog (eqepBASE_t *eqep)
{
  
  eqep->QEPCTL &= (~QEP_QEPCTL_WDE); 	
  
  return;
} /*end of QEP_disable_watchdog () function */

void QEP_enable_capture (eqepBASE_t *eqep)
{
  
  eqep->QCAPCTL |= QEP_QCAPCTL_CEN;	
  
  return;
} /*end of QEP_enable_capture () function */

void QEP_enable_counter (eqepBASE_t *eqep)
{
  
  eqep->QEPCTL |= QEP_QEPCTL_QPEN;	
  
  return;
} /*end of QEP_enable_counter () function */

void QEP_enable_gate_index (eqepBASE_t *eqep)
{
  
  eqep->QDECCTL |= QEP_Igate_Enable;	
  
  return;
} /*end of QEP_enable_gate_index () function */

void QEP_enable_interrupt (eqepBASE_t *eqep, const QEINT_t QEINT)
{
  
  eqep->QEINT |= QEINT;	
  
  return;
} /*end of QEP_enable_interrupt () function */

void QEP_enable_posn_compare (eqepBASE_t *eqep)
{
  
  eqep->QPOSCTL |= QEP_QPOSCTL_PCE;	
  
  return;
} /*end of QEP_enable_posn_compare () function */

void QEP_enable_posn_compare_shadow (eqepBASE_t *eqep)
{
  
  eqep->QPOSCTL |= QEP_QPOSCTL_PCSHDW;	
  
  return;
} /*end of QEP_enable_posn_compare_shadow () function */

void QEP_enable_sync_out (eqepBASE_t *eqep)
{
  
  eqep->QDECCTL |= QEP_QDECCTL_SOEN;
  
  return;
} /*end of QEP_enable_sync_out () function */

void QEP_enable_unit_timer (eqepBASE_t *eqep)
{
  
  eqep->QEPCTL |= QEP_QEPCTL_UTE;
  
  return; 	
} /*end of QEP_enable_unit_timer () function */

void QEP_enable_watchdog (eqepBASE_t *eqep)
{
  
  eqep->QEPCTL |= QEP_QEPCTL_WDE; 	
  
  return;
} /*end of QEP_enable_watchdog () function */

void QEP_force_interrupt (eqepBASE_t *eqep, const QEINT_t QEINT)
{
  
  eqep->QFRC |= QEINT;
  
  return;	
} /*end of QEP_force_interrupt () function */


uint16 QEP_read_capture_period_latch (eqepBASE_t *eqep)
{
  

  return eqep->QCPRDLAT;	
} /*end of QEP_read_capture_period_latch () function */

uint16 QEP_read_capture_timer_latch (eqepBASE_t *eqep)
{
  

  return eqep->QCTMRLAT;	
} /*end of QEP_read_capture_timer_latch () function */

uint16 QEP_read_interrupt_flag (eqepBASE_t *eqep, const QEINT_t QEINT)
{
  
	
	return (uint16) (eqep->QFLG & QEINT); 
} /*end of QEP_read_interrupt_flag () function */

uint32 QEP_read_posn_compare (eqepBASE_t *eqep)
{
  
  return eqep->QPOSCMP;	
} /*end of QEP_read_posn_compare () function */

uint32 QEP_read_posn_count (eqepBASE_t *eqep)
{
  
  return eqep->QPOSCNT;	
} /*end of QEP_read_posn_count () function */

uint32 QEP_read_posn_index_latch (eqepBASE_t *eqep)
{
  
  return eqep->QPOSILAT;	
} /*end of QEP_read_posn_index_latch () function */

uint32 QEP_read_posn_latch (eqepBASE_t *eqep)
{
  
  return eqep->QPOSLAT;	
} /*end of QEP_read_posn_latch () function */

uint32 QEP_read_posn_strobe_latch (eqepBASE_t *eqep)
{
  
  return eqep->QPOSSLAT;	
} /*end of QEP_read_posn_strobe_latch () function */

uint16 QEP_read_status (eqepBASE_t *eqep)
{
  
  return eqep->QEPSTS;	
} /*end of QEP_read_status () function */

void QEP_reset_counter (eqepBASE_t *eqep)
{
  
  eqep->QEPCTL &= (~QEP_QEPCTL_QPEN);
  
  return;	
} /*end of QEP_reset_counter () function */

void QEP_set_capture_latch_mode (eqepBASE_t *eqep, const QEPCTL_Qclm_t QEPCTL_Qclm)
{
  
  eqep->QEPCTL &= (~QEP_QEPCTL_QCLM);
  eqep->QEPCTL |= QEPCTL_Qclm;
  
  return;
} /*end of QEP_set_capture_latch_mode () function */

void QEP_set_capture_period (eqepBASE_t *eqep, const uint16 period)
{
  
  eqep->QCPRD = period;	
  
  return;
} /*end of QEP_set_capture_period () function */

void QEP_set_capture_prescale (eqepBASE_t *eqep, const QCAPCTL_Ccps_t QCAPCTL_Ccps)
{
  
  eqep->QCAPCTL &= (~QEP_QCAPCTL_CCPS);
  eqep->QCAPCTL |= QCAPCTL_Ccps;
} /*end of QEP_set_capture_prescale () function */

void QEP_set_emu_control (eqepBASE_t *eqep, const QEPCTL_Freesoft_t QEPCTL_Freesoft)
{
  
  eqep->QEPCTL &= (~QEP_QEPCTL_FREESOFT);
  eqep->QEPCTL |= QEPCTL_Freesoft; 	
  
  return;
} /*end of QEP_set_emu_control () function */

void QEP_set_ext_clock_rate (eqepBASE_t *eqep, const QEP_Xcr_t QEP_Xcr)
{
  
  eqep->QDECCTL &= (~QEP_QDECCTL_XCR);
  eqep->QDECCTL |= QEP_Xcr;	
  
  return;
} /*end of QEP_set_ext_clock_rate () function */

void QEP_set_index_event_init (eqepBASE_t *eqep, const QEPCTL_Iei_t QEPCTL_Iei)
{
  
  eqep->QEPCTL &= (~QEP_QEPCTL_IEI);
  eqep->QEPCTL |= QEPCTL_Iei;
  
  return;	
} /*end of QEP_set_index_event_init () function */

void QEP_set_index_event_latch (eqepBASE_t *eqep, const QEPCTL_Iel_t QEPCTL_Iel)
{
  
  eqep->QEPCTL &= (~QEP_QEPCTL_IEL);
  eqep->QEPCTL |= QEPCTL_Iel;
  
  return;
} /*end of QEP_set_index_event_latch */

void QEP_set_index_polarity (eqepBASE_t *eqep, const QEP_Qip_t QEP_Qip)
{
  
  eqep->QDECCTL &= (~QEP_QDECCTL_QIP);
  eqep->QDECCTL |= QEP_Qip;
  
  return;
} /*end of QEP_set_index_polarity () function */

void QEP_set_max_posn_count (eqepBASE_t *eqep, const uint32 max_count)
{
  
  eqep->QPOSMAX = max_count;	
  
  return;
} /*end of QEP_set_max_posn_count () function */

void QEP_set_posn_compare_pulse_width (eqepBASE_t *eqep, const uint16 pulse_width)
{
  
  uint16 pulse_width_masked;

  pulse_width_masked = pulse_width & 4095U;
  eqep->QPOSCTL &= (~QEP_QPOSCTL_PCSPW);
  eqep->QPOSCTL |= pulse_width_masked;
  
  return;
} /*end of QEP_set_posn_compare_pulse_width () function */

void QEP_set_posn_compare_shadow_load (eqepBASE_t *eqep, const QPOSCTL_Pcload_t QPOSCTL_Pcload)
{
  
  eqep->QPOSCTL &= (~QEP_QPOSCTL_PCLOAD);
  eqep->QPOSCTL |= QPOSCTL_Pcload;
  
  return;
} /*end of QEP_set_posn_compare_shadow_load () function */

void QEP_set_posn_count_reset_mode (eqepBASE_t *eqep, const QEPCTL_Pcrm_t QEPCTL_Pcrm)
{
  
  eqep->QEPCTL &= (~QEP_QEPCTL_PCRM);
  eqep->QEPCTL |= QEPCTL_Pcrm;
  
  return; 	
} /*end of QEP_set_posn_count_reset_mode () function */

void QEP_set_posn_init_count (eqepBASE_t *eqep, uint32 init_count)
{
  
  eqep->QPOSINIT = init_count;
  
  return;
} /*end of QEP_set_posn_init_count () function */

void QEP_set_select_sync_pin (eqepBASE_t *eqep, const QEP_Spsel_t QEP_SPsel)
{
  
  eqep->QDECCTL &= (~QEP_QDECCTL_SPSEL);
  eqep->QDECCTL |= QEP_SPsel;
  
  return;
} /*end of QEP_set_select_sync_pin () function */

void QEP_set_soft_init (eqepBASE_t *eqep, const QEPCTL_Swi_t QEPCTL_Swi)
{

  eqep->QEPCTL &= (~QEP_QEPCTL_SWI);
  eqep->QEPCTL |= QEPCTL_Swi;
  
  return;
} /*end of QEP_set_soft_init () function */

void QEP_set_strobe_event_init (eqepBASE_t *eqep, const QEPCTL_Sei_t QEPCTL_Sei)
{
  
  eqep->QEPCTL &= (~QEP_QEPCTL_SEI);
  eqep->QEPCTL |= QEPCTL_Sei;
  
  return;
} /*end of QEP_set_strobe_event_init () function */

void QEP_set_strobe_event_latch (eqepBASE_t *eqep, const QEPCTL_Sel_t QEPCTL_Sel)
{
  
  eqep->QEPCTL &= (~QEP_QEPCTL_SEL);
  eqep->QEPCTL |= QEPCTL_Sel;
  
  return;	
} /*end of QEP_set_strobe_event_latch () function */

void QEP_set_strobe_polarity (eqepBASE_t *eqep, const QEP_Qsp_t QEP_Qsp)
{
  
  eqep->QDECCTL &= (~QEP_QDECCTL_QSP);
  eqep->QDECCTL |= QEP_Qsp;
  
  return;
} /*end of QEP_set_strobe_polarity () function */

void QEP_set_swap_quad_inputs (eqepBASE_t *eqep, QEP_Swap_t QEP_Swap)
{
  
  eqep->QDECCTL &= (~QEP_QDECCTL_SWAP);
  eqep->QDECCTL |= QEP_Swap;
  
  return;
} /*end of QEP_set_swap_quad_inputs () function */

void QEP_set_synch_output_compare_polarity (eqepBASE_t *eqep, const QPOSCTL_Pcpol_t QPOSCTL_Pcpol)
{
  
  eqep->QPOSCTL &= (~QEP_QPOSCTL_PCPOL);
  eqep->QPOSCTL |= QPOSCTL_Pcpol;
  
  return;
} /*end of QEP_set_synch_output_compare_polarity () function */

void QEP_set_unit_period (eqepBASE_t *eqep, const uint16 unit_period)
{
  
  eqep->QUPRD = unit_period;
  
  return;	
} /*end of QEP_set_unit_period () function */

void QEP_set_unit_posn_prescale (eqepBASE_t *eqep, const QCAPCTL_Upps_t QCAPCTL_Upps)
{
  
  eqep->QCAPCTL &= (~QEP_QCAPCTL_UPPS);
  eqep->QCAPCTL |= QCAPCTL_Upps;
  
  return;
} /*end of QEP_set_unit_posn_prescale () function */

void QEP_set_watchdog_period (eqepBASE_t *eqep, const uint16 watchdog_period)
{
  
  eqep->QWDPRD = watchdog_period;
  
  return;	
} /*end of QEP_set_watchdog_period () function */

void QEP_setup_strobe_event_latch (eqepBASE_t *eqep, const QEPCTL_Sel_t QEPCTL_Sel)
{
  
  eqep->QEPCTL &= (~QEP_QEPCTL_SEL);
  eqep->QEPCTL |= QEPCTL_Sel;
  
  return;
} /*end of QEP_setup_strobe_event_latch () function */


void QEP_set_A_polarity (eqepBASE_t *eqep, const QEP_Qap_t QEP_Qap)
{
  
  eqep->QDECCTL &= (~QEP_QDECCTL_QAP);
  eqep->QDECCTL |= QEP_Qap;
  
  return;
} /*end of QEP_set_A_polarity () function */

void QEP_set_B_polarity (eqepBASE_t *eqep, const QEP_Qbp_t QEP_Qbp)
{
  
  eqep->QDECCTL &= (~QEP_QDECCTL_QBP);
  eqep->QDECCTL |= QEP_Qbp;
  
  return;
} /*end of QEP_set_B_polarity () function */

void QEP_set_QEP_source (eqepBASE_t *eqep, const QEP_Qsrc_t QEP_Qsrc)
{
    
  /* set the value */
  eqep->QDECCTL &= (~QEP_QDECCTL_QSRC);
  eqep->QDECCTL |= QEP_Qsrc;
  
  return;
} /*end of QEP_set_QEP_source () function */

void QEP_write_posn_compare (eqepBASE_t *eqep, const uint32 posn)
{
  
  eqep->QPOSCMP = posn;
  
  return;
} /*end of QEP_write_posn_compare () function */


/*end of file*/
