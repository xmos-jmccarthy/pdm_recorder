// Copyright (c) 2023 XMOS LIMITED. This Software is subject to the terms of the
// XMOS Public License: Version 1

#include <platform.h>
#include <xscope.h>

extern "C" {
void cmain_xscope_pdm(chanend c_xscope_host);
}

int main(void) {
    chan c_xscope_host;
    par {
        xscope_host_data(c_xscope_host);
        on tile[1] : cmain_xscope_pdm(c_xscope_host);
    }
    return 0;
}