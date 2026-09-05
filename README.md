# libvirt setup for lab on university

## Virtual Disk
- **Kali**
  - Download with `curl -LO https://cdimage.kali.org/kali-2026.2/kali-linux-2026.2-qemu-amd64.7z && 7z x $_`
- **Metasploitable2**
  - Download from [sourceforge](https://sourceforge.net/projects/metasploitable/)
  - Then `unzip metasploitable-linux-2.0.0.zip && cd Metasploitable2-Linux`
  - Convert to .qcow `qemu-img convert -f vmdk Metasploitable.vmdk -O qcow2 Metasploitable.qcow2`

- Move .qcow2 file to `virsh vol-list --pool default` directory

## Network
- `virsh net-define <network>.xml`
- `virsh net-start <network>.xml`
- `virsh net-autostart <network>.xml`

## Create Virual Machine (VM)
- `virsh define <name>.xml`
- `virsh start <name>.xml`

## Tip
- `virsh console <domain-name>` - I setup to use serial tty (/dev/ttySx) for access VM without `ssh`
- `virt-viewer` for Graphical Display
