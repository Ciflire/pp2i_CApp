# flake.nix
{
  inputs = { nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable"; };

  outputs = { nixpkgs, ... }:
    let
      system = "x86_64-linux";
      #       ↑ Swap it for your system if needed
      #       "aarch64-linux" / "x86_64-darwin" / "aarch64-darwin"
      pkgs = nixpkgs.legacyPackages.${system};
    in {
      devShells.${system}.default =
        pkgs.mkShell.override { stdenv = pkgs.clangStdenv; } {
          packages = [
            pkgs.gnumake
            pkgs.clang
            pkgs.rocmPackages.llvm.lldb
            pkgs.rocmPackages.llvm.clang-tools-extra
          ];

          LIBRARY_PATH = "${pkgs.glibc}/include";
        };

    };
}
