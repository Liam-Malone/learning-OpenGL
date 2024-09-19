{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
  };

  outputs = { self, nixpkgs,... }:
    let
      supportedSystems = [ "x86_64-linux" "aarch64-linux" "x86_64-darwin" "aarch64-darwin" ];
      forEachSupportedSystem = f: nixpkgs.lib.genAttrs supportedSystems (system: f {
        pkgs = import nixpkgs { inherit system; };
      });
    in
    {
      devShells = forEachSupportedSystem({ pkgs }: {
        default = pkgs.mkShell {
          buildInputs = with pkgs; [
            alsa-lib
            clang
            gcc
            gdb
            gf
            glfw
            gtk3
            gtk4
            libGL
            libdecor
            libpulseaudio
            libxkbcommon
            mesa
            python3
            wayland
            xorg.libX11
            xorg.libX11.dev
            xorg.libXi
            xorg.libXinerama
            xorg.libXcursor
            xorg.libXrandr
            xorg.libxcb
            xorg.xinput
            zig
          ];

          shellHook = ''
            alias build='./build.sh'
            alias test='./test.sh'
            alias serve='python3 -m http.server 8080'
            alias gl_site='cd learnopengl.com; serve &>/dev/null &disown; cd -'
            export CC='zig cc'
          '';
        };
      });
    };
}
