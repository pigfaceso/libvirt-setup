# libvirt setup

## libvirt install

### Fedora

- Install the virtualization group:

  ```bash
  sudo dnf install @virtualization
  ```

  - List hidden groups: `dnf group list --hidden`
  - Show group details: `dnf group info <group-name>`

- Add your user to the `libvirt` and `kvm` groups:

  ```bash
  sudo usermod -aG libvirt,kvm $USER
  ```

- Enable and start `libvirtd`:

  ```bash
  sudo systemctl enable --now libvirtd
  ```

## Virtual disk

### Kali

Download and extract the image:

```bash
curl -LO https://cdimage.kali.org/kali-2026.2/kali-linux-2026.2-qemu-amd64.7z
7z x kali-linux-2026.2-qemu-amd64.7z
```

### Metasploitable 2

- Download from [SourceForge](https://sourceforge.net/projects/metasploitable/).
- Extract the archive and enter the directory:

  ```bash
  unzip metasploitable-linux-2.0.0.zip
  cd Metasploitable2-Linux
  ```

- Convert the VMDK disk to qcow2:

  ```bash
  qemu-img convert -f vmdk Metasploitable.vmdk -O qcow2 Metasploitable.qcow2
  ```

### MSEdge-Win10

- Download from [MSEdge-Win10 | Archive](https://archive.org/download/msedge.win10.vmware.galoget)
  ```bash
  unzip MSEdge.Win10.VMware.zip
  cd MSEdge-Win10-VMware
  ```
- Convert the VMDK disk to qcow2:

  ```bash
  qemu-img convert -f vmdk MSEdge-Win10-VMware-disk1.vmdk -O qcow2 MSEdge-Win10-VMware.qcow2
  ```

Move the `.qcow2` file into the `default` storage pool directory. Find that directory with `virsh vol-list --pool default` (requires `sudo`).

## Virtual network

- `virsh net-define network/<network>.xml` — define a network from an XML file.
- `virsh net-list [--all]` — list all networks.
- `virsh net-start <network>` — start a network.
- `virsh net-destroy <network>` — destroy network.
- `virsh net-autostart <network>` — start a network automatically.
- `virsh net-dhcp-leases <network>` — list IP addresses leased by the virtual network interface.

> See the [libvirt network XML format](https://libvirt.org/formatnetwork.html) for more details.

## Virtual machine (VM)

Create a VM:

```bash
virt-install \
  --name <name> \
  --vcpus <cpu cores, e.g. 2> \
  --memory <memory in MiB, e.g. 8192> \
  --disk vol=<pool/volume, e.g. default/kali.qcow2> \
  --import \
  --network network=<network> \
  --network network=<network> \
  --osinfo <libvirt-osinfo>
```

- `virsh list [--all]` — list all VMs.
- `virsh start <name>` — start a VM.
- `virsh destroy <name>` — shut down a VM.

List all supported osinfo values with `virt-install --osinfo list`:

- Kali — `debain13`
- Metasploitable 2 — `ubuntu8.04`

## Tips

- `virsh console <domain-name>` — access a VM without SSH using the serial TTY (`/dev/ttySx`). Configure it with `virt-install <...> --serial <option>`. Some images use an old SSH service.
- `virt-viewer` — graphical display for libvirt using [SPICE (Remote Desktop Protocol)](https://www.spice-space.org).
- `virt-manager` — libvirt GUI.

## Reference

- [virsh (libvirt CLI) from Red Hat](https://docs.redhat.com/en/documentation/red_hat_enterprise_linux/7/html/virtualization_deployment_and_administration_guide/chap-managing_guest_virtual_machines_with_virsh)
- [Setup libvirt from Fedora](https://developer.fedoraproject.org/tools/virtualization/setting-up-fedora-workstation-domain-on-libvirt.html)
- [libvirt XML format](https://libvirt.org/format.html)
