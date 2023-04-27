// Copyright (c) 2023 XMOS LIMITED. This Software is subject to the terms of the
// XMOS Public License: Version 1

#include <platform.h>
#include <stdio.h>
#include <stdint.h>
#include <stdint.h>
#include <xscope.h>

#include <xcore/port.h>
#include <xcore/chanend.h>
#include <xcore/clock.h>
#include <xcore/hwtimer.h>
#include <xcore/assert.h>

#define MCLK_FREQ   24576000
#define PDM_FREQ     3072000

#define APP_PLL_CTL_VAL   0x0A019803 // Valid for all fractional values
#define APP_PLL_FRAC_NOM  0x800095F9 // 24.576000 MHz

void app_pll_init(void)
{
    unsigned tileid = get_local_tile_id();

    const unsigned APP_PLL_DISABLE = 0x0201FF04;
    const unsigned APP_PLL_DIV_0   = 0x80000004;

    write_sswitch_reg(tileid, XS1_SSWITCH_SS_APP_PLL_CTL_NUM, APP_PLL_DISABLE);

    hwtimer_t tmr = hwtimer_alloc();
    {
        xassert(tmr != 0);
        hwtimer_delay(tmr, 100000); // 1ms with 100 MHz timer tick
    }
    hwtimer_free(tmr);

    write_sswitch_reg(tileid, XS1_SSWITCH_SS_APP_PLL_CTL_NUM, APP_PLL_CTL_VAL);
    write_sswitch_reg(tileid, XS1_SSWITCH_SS_APP_PLL_CTL_NUM, APP_PLL_CTL_VAL);
    write_sswitch_reg(tileid, XS1_SSWITCH_SS_APP_PLL_FRAC_N_DIVIDER_NUM, APP_PLL_FRAC_NOM);
    write_sswitch_reg(tileid, XS1_SSWITCH_SS_APP_CLK_DIVIDER_NUM, APP_PLL_DIV_0);
}


void pdm_setup(void) {
    uint32_t divide = MCLK_FREQ / PDM_FREQ;

    xclock_t pdmclk = XS1_CLKBLK_1;
    port_t p_mclk = PORT_MCLK_IN_OUT;
    port_t p_pdm_clk = PORT_PDM_CLK;
    port_t p_pdm_mics = PORT_PDM_DATA;

    /* Setup DDR mics */
    clock_enable(pdmclk);
    port_enable(p_mclk);
    clock_set_source_port(pdmclk, p_mclk);
    clock_set_divide(pdmclk, divide/2);

    port_enable(p_pdm_clk);
    port_set_clock(p_pdm_clk, pdmclk);
    port_set_out_clock(p_pdm_clk);

    port_start_buffered(p_pdm_mics, 32);
    port_set_clock(p_pdm_mics, pdmclk);
    port_clear_buffer(p_pdm_mics);
}


void pdm_start(void) {
    xclock_t pdmclk = XS1_CLKBLK_1;
    port_t p_pdm_mics = PORT_PDM_DATA;

    port_clear_buffer(p_pdm_mics);
    clock_start(pdmclk);
}


void cmain_xscope_pdm(chanend_t c_xscope_host)
{
    xscope_mode_lossless();
    xscope_connect_data_from_host(c_xscope_host);
    app_pll_init();
    pdm_setup();
    pdm_start();
    printf("Start sending data\n");
    
    while(1) {
        xscope_int(PDM, port_in(PORT_PDM_DATA));
    }
}
