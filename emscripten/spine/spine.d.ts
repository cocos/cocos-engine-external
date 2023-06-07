declare module 'external:emscripten/spine/spine.asm.js' {
    export default SpineWasm;
}

declare module 'external:emscripten/spine/spine.js' {
    export default SpineWasm;
}

// tslint:disable
declare function SpineWasm (moduleOptions?: any): Promise<void>;

declare namespace SpineWasm {
    type ptr = number;
    interface instance {
        spine: any;
        memory: any;
        spineWasmInit(): void;
        spineWasmDestroy(): void;
    }
}
