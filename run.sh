#!/bin/bash
set -e

docker run --name mac-container -it --rm --network host -v ~/.bash_history:/root/.bash_history -v ./app:/app mac_dev:latest bash
