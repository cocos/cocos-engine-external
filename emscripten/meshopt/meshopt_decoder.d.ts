declare module 'external:emscripten/meshopt/meshopt_decoder.asm.js' {
    namespace MeshoptDecoder {
        const supported: boolean;
        const ready: Promise<void>;

        function decodeVertexBuffer (target: Uint8Array, count: number, size: number, source: Uint8Array, filter?: string): void;
        function decodeIndexBuffer (target: Uint8Array, count: number, size: number, source: Uint8Array): void;
        function decodeIndexSequence (target: Uint8Array, count: number, size: number, source: Uint8Array): void;

        function decodeGltfBuffer (target: Uint8Array, count: number, size: number, source: Uint8Array, mode: string, filter?: string): void;

        function useWorkers (count: number): void;
        function decodeGltfBufferAsync (count: number, size: number, source: Uint8Array, mode: string, filter?: string): Promise<Uint8Array>;
    }

    export default MeshoptDecoder;
}

declare module 'external:emscripten/meshopt/meshopt_decoder.wasm.js' {
    namespace MeshoptDecoder {
        const supported: boolean;
        const ready: (instantiateWasm: any) => Promise<void>;

        function decodeVertexBuffer (target: Uint8Array, count: number, size: number, source: Uint8Array, filter?: string): void;
        function decodeIndexBuffer (target: Uint8Array, count: number, size: number, source: Uint8Array): void;
        function decodeIndexSequence (target: Uint8Array, count: number, size: number, source: Uint8Array): void;

        function decodeGltfBuffer (target: Uint8Array, count: number, size: number, source: Uint8Array, mode: string, filter?: string): void;

        function useWorkers (count: number): void;
        function decodeGltfBufferAsync (count: number, size: number, source: Uint8Array, mode: string, filter?: string): Promise<Uint8Array>;
    }

    export default MeshoptDecoder;
}
