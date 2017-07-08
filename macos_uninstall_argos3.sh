#!/usr/bin/env bash -e

echo '====================='
echo '= ARGoS Uninstaller ='
echo '====================='
echo
echo 'To complete this operation, you will need administrative privileges.'
echo
read -p 'Press CTRL-C to exit, or any other key to proceed...'
echo
echo 'Uninstalling ARGoS3... '
sudo rm -rf /usr/local/bin/argos3
sudo rm -rf /usr/local/doc/argos3
sudo rm -rf /usr/local/include/argos3
sudo rm -rf /usr/local/lib/argos3
sudo rm -rf /usr/local/lib/pkgconfig/argos3_simulator.pc
sudo rm -rf /usr/local/libexec/argos3
sudo rm -rf /usr/local/share/man/man1/argos3.1.gz
sudo rm -rf /usr/local/share/argos3
