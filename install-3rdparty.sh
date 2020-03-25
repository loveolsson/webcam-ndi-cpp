#!/bin/bash

DIRECTORY=`dirname $0`

cd $DIRECTORY

mkdir -p 3rdParty
cd 3rdParty

OS="`uname`"
case $OS in
  'Linux')
    OS='Linux'
    ;;
  'Darwin') 
    curl -L http://new.tk/NDISDKAPPLE -o InstallNDISDK.pkg
    pkgutil --expand-full InstallNDISDK.pkg NDI-EXTRACT
    mv NDI-EXTRACT/NDI_SDK_Component.pkg/Payload/NDI\ SDK\ for\ Apple/ ./NDI-SDK
    rm -rf NDI-EXTRACT/
    rm InstallNDISDK.pkg
    ;;
  *) 
    exit 1
  ;;
esac

