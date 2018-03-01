# C# Demos

## Overview

This directory contains C# sample programs for various Ice components. These
examples are provided to get you started on using a particular Ice feature or
coding technique.

Most of the subdirectories here correspond directly to Ice components, such as
[Glacier2](./Glacier2), [IceBox](./IceBox), and so on. We've also included the
following additional subdirectories:

- [Manual](./Manual) contains complete examples for some of the code snippets
in the [Ice manual][1].

- [Chat](./Chat) contains a .NET GUI client for the ZeroC [Chat Demo][2].

Refer to the [C++11 demos](../cpp11) for more examples that use the Ice services
(Glacier2, IceGrid, IceStorm).

## Building and running the Demos with .NET Framework on Windows

### Build Requirements

In order to build Ice for .NET sample programs, you need a supported version
of Visual Studio.

### Building the demos using NuGet packages:

Open the solution file `C# NET Framework demos.sln` to build the sample programs.

The demos are configured to use the Ice distribution from NuGet packages. These
packages are automatically downloaded during the build. If you have disabled the
automatic download of NuGet packages in Visual Studio, you need to restore the
packages before you build.

Packages can be restored via `Tools > NuGet Package Manager > Manage NuGet
Packages for Solution...` in Visual Studio.

After restoring the packages, right click on the desired demo in the Solution
Explorer window and select `Build`.

### Building the demos using a source build:

- Build from command line:
  * Open a Visual Studio command prompt
  ```
  cd ice-demos\csharp
  MSBuild /p:IceHome=<Ice dist path> /t:Net45Build msbuild\ice.proj
  ```

- Build from Visual Studio:
  * Open a Visual Studio command prompt
  ```
  cd ice-demos\csharp
  MSBuild /p:IceHome=<Ice dist path> /t:Net45InstallLocalPackages msbuild\ice.proj
  ```

  * Open the solution file `C# NET Framework demos.sln` to build the sample programs.

### Running the Demos

For most demos, you can simply run `client` and `server` in separate Command
Prompt windows.  Refer to the README.md file in each demo directory for the
exact usage instructions.

Some demos require Ice services such as IceGrid and IceStorm that are not
included in the `zeroc.ice.net` NuGet package. To run these demos, the simplest
is to first install the Ice MSI and add its bin directory to your PATH. Please
refer to [Using the Windows Binary Distributions][4] for additional information.

## Building and running the Demos with .NET Core on Windows, Linux, and macOS

### Build Requirements

In order to build Ice for .NET sample programs, you need all of the following:

 - the [.NET Core 2.0 SDK][5]
 - Slice to C# compiler, for Windows platform the Slice to C# compiler is included
   with the `zeroc.ice.net` NuGet package installed during build, for other platforms
   refer to the [Release Notes][6].

### Building the demos using NuGet packages:

Open a command prompt and change to the `csharp` subdirectory:

```
cd csharp
```

To build the sample programs run:

```
dotnet msbuild "C# NET Core demos.sln" /t:"Restore;Build"
```

The demos are configured to use the Ice distribution from NuGet packages. These
packages are automatically downloaded during the build.

### Building the demos using a source build:

Open a command prompt and change to the `csharp` subdirectory:

```
cd csharp
```

Install packages from the source build:

On Windows

```
msbuild /p:IceHome=<Ice dist path> /t:NetStandardInstallLocalPackages msbuild\ice.proj
```

On Linux and macOS

```
dotnet msbuild /p:IceHome=<Ice dist path> /t:NetStandardInstallLocalPackages msbuild/ice.proj
```

To build the sample programs run:

```
dotnet msbuild "C# NET Core demos.sln" /t:"Restore;Build"
```

### Running the Demos

For most demos, you can simply run `dotnet client.dll` and `dotnet server.dll` in
separate Command Prompt windows.  Refer to the README.md file in each demo directory
for the exact usage instructions.

Some demos require Ice services such as IceGrid and IceStorm that are not
included in the `zeroc.ice.net` NuGet package. To run these demos, the simplest
is to first install the Ice binary distribution for your platform  and add its bin
directory to your PATH. Please refer to the [Release Notes][6] for additional information.

[1]: https://doc.zeroc.com/display/Ice37/Ice+Manual
[2]: https://zeroc.com/chat/index.html
[4]: https://doc.zeroc.com/display/Rel/Using+the+Windows+Binary+Distributions+for+Ice+3.7.1
[5]: https://www.microsoft.com/net/download/windows
[6]: https://doc.zeroc.com/display/Ice37/Ice+Release+Notes
