declare module 'external:emscripten/spine/3.8/spine.asm.js' {
    export default SpineWasm;
}

declare module 'external:emscripten/spine/3.8/spine.wasm.js' {
    export default SpineWasm;
}

declare module 'external:emscripten/spine/4.2/spine.asm.js' {
    export default SpineWasm;
}

declare module 'external:emscripten/spine/4.2/spine.wasm.js' {
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
