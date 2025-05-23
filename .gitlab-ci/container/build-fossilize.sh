#!/bin/bash

# When changing this file, you need to bump the following
# .gitlab-ci/image-tags.yml tags:
# DEBIAN_TEST_VK_TAG

set -ex

uncollapsed_section_start fossilize "Building fossilize"

git clone https://github.com/ValveSoftware/Fossilize.git
cd Fossilize
git checkout b43ee42bbd5631ea21fe9a2dee4190d5d875c327
git submodule update --init
mkdir build
cd build
cmake -S .. -B . -G Ninja -DCMAKE_BUILD_TYPE=Release
ninja -C . install
cd ../..
rm -rf Fossilize

section_end fossilize
