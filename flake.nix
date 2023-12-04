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
      inherit system;
    };
  in {
    packages.${system}.default = pkgs.stdenv.mkDerivation {
      name = "mfgd";
      src = ./.;

      nativeBuildInputs = [
        pkgs.makeWrapper
      ];

      buildInputs = [
        pkgs.glfw
        pkgs.darwin.apple_sdk.frameworks.ApplicationServices
        pkgs.darwin.apple_sdk.frameworks.OpenGL
      ];

      installPhase = ''
        mkdir -p $out/bin
        cp mfgd $out/bin/mfgd

        mkdir -p $out/resources
        cp -r resources/* $out/resources

        wrapProgram $out/bin/mfgd --prefix C_RESOURCE_PATH : $out/resources
      '';
    };

    formatter.${system} = pkgs.alejandra;
  };
}
