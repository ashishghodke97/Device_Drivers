cmd_/home/ashish/device_drivers/native_compiler/export_symbol/modules.order := {   echo /home/ashish/device_drivers/native_compiler/export_symbol/avg.ko;   echo /home/ashish/device_drivers/native_compiler/export_symbol/add.ko; :; } | awk '!x[$$0]++' - > /home/ashish/device_drivers/native_compiler/export_symbol/modules.order
