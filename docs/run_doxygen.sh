#!/bin/bash

if [ -d docBin ]; then
    rm -rf docBin
fi

sed -e 's/ROCFFT_EXPORT //g' ../library/include/rocfft/rocfft.h > rocfft.h
doxygen Doxyfile
rm rocfft.h

