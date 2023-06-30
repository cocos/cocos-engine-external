declare module 'external:emscripten/spine/spine.asm.js' {
    export default SpineWasm;
}

declare module 'external:emscripten/spine/spine.wasm.js' {
    export default SpineWasm;
}

// tslint:disable
declare function SpineWasm (moduleOptions?: any): Promise<void>;

declare namespace SpineWasm {
    interface instance {
        spineWasmInit(): void;
        spineWasmDestroy(): void;
    }
}
