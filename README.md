# libvirt setup

## libvirt intstall
### Fedora
- `sudo dnf install @virtualization` (try `dnf group list --hidden` and `dnf group info <group-name>`)
- `sudo usermod -aG libvirt,kvm $USER`
- `sudo systemctl enable --now libvirtd`

## Virtual Disk
### Kali
  - Download from `curl -LO https://cdimage.kali.org/kali-2026.2/kali-linux-2026.2-qemu-amd64.7z && 7z x $_`
### Metasploitable2
  - Download from [sourceforge](https://sourceforge.net/projects/metasploitable/)
  - Then `unzip metasploitable-linux-2.0.0.zip && cd Metasploitable2-Linux`
  - Convert to .qcow `qemu-img convert -f vmdk Metasploitable.vmdk -O qcow2 Metasploitable.qcow2`

Move .qcow2 file to `virsh vol-list --pool default` directory (require `sudo`)

## Virtual Network
- `virsh net-define network/<network>.xml`
- `virsh net-list [--all]` List all network
- `virsh net-start <network>`
- `virsh net-autostart <network>`
- `virsh net-dhcp-leases <network>` List using ip from virtual network interface

> Find more about [libvirt network XML format](https://libvirt.org/formatnetwork.html)

## Virtual Machine (VM)
- `virt-install --name <name> --vcpus <cpu core eg. 2> --memory <memory (MiB) eg. 8192> --disk vol=<[vol-name]/[QCOW2 file] eg. default/kali.qcow2> --import --network network=<network> --network network=<network> --osinfo <libvirt-osinfo>`.
- `virsh list [--all]` List all VM
- `virsh start <name>` Start VM
- `virsh destroy <name>` Shutdown VM

> List of all osinfo on libvirt `virt-install --osinfo list`
>> Kali - `debain13`
>> 
>> Metasploitable2 - `ubuntu8.04`

## Tip

- `virsh console <domain-name>` I setup to use serial tty (/dev/ttySx) for access VM without `ssh` (`virt-install <...> --serial <option>`)(Some virtual images use old ssh service)
- `virt-viewer` - libvirt Graphical Display using [SPICE (Remote Desktop Protocol)](https://www.spice-space.org)
- `virt-manager` libvirt GUI

# Reference
- [virsh (libvirt CLI) from RedHat](https://docs.redhat.com/en/documentation/red_hat_enterprise_linux/7/html/virtualization_deployment_and_administration_guide/chap-managing_guest_virtual_machines_with_virsh)
- [Setup libvirt from Fedora](https://developer.fedoraproject.org/tools/virtualization/setting-up-fedora-workstation-domain-on-libvirt.html)
- [libvirt XML format](https://libvirt.org/format.html)
