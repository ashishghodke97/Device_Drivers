cmd_/home/ashish/device_drivers/native_compiler/param/Module.symvers := sed 's/ko$$/o/' /home/ashish/device_drivers/native_compiler/param/modules.order | scripts/mod/modpost -m -a   -o /home/ashish/device_drivers/native_compiler/param/Module.symvers -e -i Module.symvers   -T -
