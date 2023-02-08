# Protobuf

[Protocol buffers (aka protobuf)](https://developers.google.com/protocol-buffers/docs/overview) are language-neutral, platform-neutral, extensible mechanism for serializing structured data.

## Installation

### MacOS X
```bash
brew install python-protobuf
pip3 install --upgrade protobuf
protoc --version
which protoc
```
 
> Version is `libprotoc 3.20.1`


## Encoding and Decoding

```bash
protoc --encode=Telemetry telemetry.proto < telemetry.text  > binary.data
hexdump -C binary.data
protoc --decode Telemetry telemetry.proto < binary.data
```

## Codec library generation

See the `[telemetry.proto](./telemetry.proto)` description

```bash
cd ~/github/campusiot/tutorial/protobuf
cat telemetry.proto
mkdir -p target/python
protoc --python_out=target/python telemetry.proto
mkdir -p target/cpp
protoc --cpp_out=target/cpp telemetry.proto
mkdir -p target/js
protoc --js_out=target/js telemetry.proto
mkdir -p target/java
protoc --java_out=target/java telemetry.proto
```

## `nanopb`

[Nanopb](https://github.com/nanopb/nanopb) is a small code-size Protocol Buffers implementation in ansi C. It is especially suitable for use in microcontrollers, but fits any memory restricted system.

Install:
```bash
mkdir -p ~/github/nanopb
cd ~/github/nanopb
git clone https://github.com/nanopb/nanopb
cd nanopb
```

Build:
```bash
cd examples/using_union_messages
make
```

Run
```
> ./encode 1 | hexdump -C
00000000  0a 02 08 2a
00000004                       
> ./encode 1 | ./decode
Got MsgType1: 42
> ./encode 2 | hexdump -C
00000000  12 02 08 01
00000004                       
> ./encode 2 | ./decode
Got MsgType2: true
```

## Protobuf with RIOT OS (`nanopb` package)

RIOT OS provides `nanopb` as a package

```bash
BOARD=im880b
cd ~/github/RIOT-OS/RIOT/tests/pkg_nanopb
make BOARD=$BOARD flash term
```


## More
* [Convert JSON to Protobuf and back](https://github.com/iamazeem/proto-convert)
* https://blog.basyskom.com/2020/protobuf-for-iot/
* https://embeddedproto.com/a-simple-arduino-iot-example-with-protobuf/
* https://itnext.io/iot-telemetry-collection-using-google-protocol-buffers-cloud-functions-pub-sub-and-mongodb-atlas-d5e4ff7ef50e

