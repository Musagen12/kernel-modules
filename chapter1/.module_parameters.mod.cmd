savedcmd_module_parameters.mod := printf '%s\n'   module_parameters.o | awk '!x[$$0]++ { print("./"$$0) }' > module_parameters.mod
