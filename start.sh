#!/usr/bin/env bash

virsh net-start hostonly
virsh net-start nat

virsh start kali
virsh start metasploitable2
