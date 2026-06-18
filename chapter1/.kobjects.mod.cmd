savedcmd_kobjects.mod := printf '%s\n'   kobjects.o | awk '!x[$$0]++ { print("./"$$0) }' > kobjects.mod
