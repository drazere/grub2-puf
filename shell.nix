{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  buildInputs = with pkgs; [
    gcc
    gnumake
    autoconf
    automake
    libtool
    autoconf-archive
    gettext
    flex
    bison
    pkg-config
    texinfo
    help2man
    python3
  ];

  shellHook = ''
    export NIX_CFLAGS_COMPILE="-fno-pie -Wno-error"
    export NIX_CFLAGS_LINK="-no-pie"
    export CFLAGS="-O2 -g -fno-pie -Wno-error"
    export CPPFLAGS="-Wno-error"
    export LDFLAGS="-no-pie"

    echo "GRUB dev environment ready (PIE disabled, Werror disabled)"
  '';
}
