declare module 'external:emscripten/webgpu/webgpu_wasm.js' {
    function factory (gfx: any): Promise<any>;
    export default factory;
}

declare module 'external:emscripten/webgpu/glslang.js' {
    function factory (options?: any): Promise<any>;
    export default factory;
}

declare module 'external:emscripten/webgpu/twgsl.js' {
    function factory (options?: any): Promise<any>;
    export default factory;
}
