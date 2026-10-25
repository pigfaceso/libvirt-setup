#!/usr/bin/env bash

virsh destroy kali
virsh destroy metasploitable2

virsh net-destroy hostonly
virsh net-destroy nat
