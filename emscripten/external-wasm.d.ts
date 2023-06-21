declare module 'external:emscripten/*.wasm' {
    /**
     * This is a wasm url relative from build output chunk.
     */
    const wasmPath: string;
    export default wasmPath;
}

declare module 'external:emscripten/*.wasm.fallback' {
    /**
     * This is a wasm fallback url relative from build output chunk.
     */
    const wasmFallbackPath: string;
    export default wasmFallbackPath;
}

declare module 'external:emscripten/*.js.mem' {
    /**
     * This is a js.mem url relative from build output chunk.
     */
    const jsMemPath: string;
    export default jsMemPath;
}