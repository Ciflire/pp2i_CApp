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
        pkgs.mkShell.override { stdenv = pkgs.clang15Stdenv; } {
          packages = [
            pkgs.gdb

            # Choose the build tools that you need
            pkgs.gnumake
            pkgs.llvmPackages_9.clang-unwrapped
            pkgs.rocmPackages.llvm.lldb

          ];
        };

    };
}
