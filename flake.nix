{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";
  };
  outputs = {
    self,
    nixpkgs,
  }: let
    system = "aarch64-darwin";
    pkgs = import nixpkgs {
      system = system;
    };
  in {
    packages.${system}.default = pkgs.stdenv.mkDerivation {
      name = "mfgd";
      src = ./.;

      buildInputs = [
        pkgs.stdenv
        pkgs.glfw
        pkgs.darwin.apple_sdk.frameworks.ApplicationServices
        pkgs.darwin.apple_sdk.frameworks.OpenGL
      ];

      installPhase = ''
        mkdir -p $out/bin
        cp mfgd $out/bin/mfgd

        mkdir -p $out/resources
        cp -r resources/ $out/resources/
      '';
    };

    formatter.${system} = pkgs.alejandra;
  };
}