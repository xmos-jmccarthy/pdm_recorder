// Copyright (c) 2023 XMOS LIMITED. This Software is subject to the terms of the
// XMOS Public License: Version 1

#include <platform.h>
#include <xscope.h>

extern "C" {
void cmain_xscope(chanend c_xscope_host, chanend c_sync);
void cmain_pdm(chanend c_sync);
}

int main(void) {
    chan c_xscope_host;
    chan c_sync;
    par {
        xscope_host_data(c_xscope_host);
        on tile[1] : cmain_xscope(c_xscope_host, c_sync);
        on tile[1] : cmain_pdm(c_sync);
    }
    return 0;
}