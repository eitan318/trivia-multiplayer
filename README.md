# Trivia Multiplayer

A real-time multiplayer trivia game built around a custom TCP protocol. The
project pairs a high-performance C++ server with a modern WPF desktop client,
and ships with full account management, live multiplayer rooms, quick 1v1
matchmaking, and persistent statistics.

<img width="1524" height="823" alt="image" src="https://github.com/user-attachments/assets/c36aec32-b3bc-4c56-81f4-bc1edb622b68" />


## Features

- **Account system** — sign up, log in, and recover access through an
  email-verified password reset flow (Gmail SMTP).
- **Secure credentials** — passwords are hashed before being stored.
- **Multiplayer rooms** — create rooms, configure question count and time
  limit, join other players, and play together in real time.
- **1v1 quick match** — automatic matchmaking against another waiting player.
- **Question pool** — questions are pulled from the
  [Open Trivia Database](https://opentdb.com/) and can be supplemented with
  user-submitted questions.
- **Statistics & high scores** — per-user stats and a global leaderboard,
  persisted in SQLite.
- **MVVM desktop UI** — Material Design themed WPF client with dependency
  injection and view-model navigation.

## Architecture

The repository contains three top-level components:

| Folder | Component | Stack |
|---|---|---|
| `M_Trivia/` | Game server | C++17, WinSock2, SQLite, libcurl, vcpkg |
| `ClientApp/` | Desktop client | C# / .NET 8, WPF, CommunityToolkit.Mvvm, MaterialDesignThemes |
| `TriviaProgramDesign/` | Design documents | draw.io diagrams, Word doc |

The client and server communicate over a custom binary protocol on TCP port
`5554`. Each request is encoded as a one-byte op-code followed by a 4-byte
big-endian payload length and a JSON payload; responses follow the same
framing. Op-codes are defined in
[`M_Trivia/M_Trivia/RequestsCodes.hpp`](M_Trivia/M_Trivia/RequestsCodes.hpp).

High-level design diagrams (request/response shapes and module breakdown) live
in `TriviaProgramDesign/` and can be opened with [draw.io](https://app.diagrams.net/).

## Requirements

### Server (`M_Trivia`)
- Windows 10 / 11 (uses WinSock2)
- Visual Studio 2022 with the **Desktop development with C++** workload, or
  CMake 3.10+ with an MSVC toolchain
- [vcpkg](https://github.com/microsoft/vcpkg) (libcurl is pulled in via
  `vcpkg.json`)

### Client (`ClientApp`)
- Windows 10 / 11
- [.NET 8 SDK](https://dotnet.microsoft.com/download/dotnet/8.0)
- Visual Studio 2022 (recommended) with the **.NET desktop development**
  workload

## Building & Running

### 1. Start the server

Open `M_Trivia/M_Trivia.sln` in Visual Studio, select the `x64` configuration,
and build & run the `M_Trivia` project. The server will bind to port `5554`
and create / open `trivia_db.sqlite` next to the executable.

Alternatively, with CMake:

```sh
cd M_Trivia
cmake -B build -S .
cmake --build build --config Release
./build/Release/main.exe
```

### 2. Launch the client

Open `ClientApp/ClientApp.sln` in Visual Studio and run the `ClientApp`
project, or from the command line:

```sh
cd ClientApp/ClientApp
dotnet run
```

The client connects to `127.0.0.1:5554` by default. To target a remote server,
update the `SocketService` registration in
[`ClientApp/ClientApp/App.xaml.cs`](ClientApp/ClientApp/App.xaml.cs).

## Project Layout

```
trivia-multiplayer/
├── ClientApp/                # WPF desktop client (MVVM)
│   └── ClientApp/
│       ├── ViewModels/       # Screen and control view-models
│       ├── Views/            # XAML views, controls, converters
│       ├── Services/         # Networking, navigation, serialization
│       ├── Stores/           # Shared application state
│       ├── Commands/         # ICommand implementations
│       └── Models/           # Request / response DTOs
├── M_Trivia/                 # C++ game server
│   ├── M_Trivia/             # Server source, handlers, managers
│   └── ClientServer/         # Reference Python client/server (protocol sandbox)
└── TriviaProgramDesign/      # Architecture diagrams and design document
```

## Configuration Notes

- **OpenTDB** — the server fetches questions from `opentdb.com` over HTTPS
  using libcurl. An internet connection is required when starting a new game
  with API-sourced questions.
- **SMTP / Email** — password reset codes are sent via Gmail SMTP. Provide a
  Gmail account and an app password through the appropriate configuration
  before using the password reset flow in production.
- **Database** — `trivia_db.sqlite` is created automatically on first run.

## Authors

Developed by Eliya and Yaniv (2025).
