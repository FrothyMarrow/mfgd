let 
  pkgs = import <nixpkgs> {};
in 
  pkgs.mkShell {
    buildInputs = [
      pkgs.stdenv
      pkgs.glfw
      pkgs.darwin.apple_sdk.frameworks.ApplicationServices
      pkgs.darwin.apple_sdk.frameworks.OpenGL
    ];
  }