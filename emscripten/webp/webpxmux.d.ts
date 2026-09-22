// Emscripten module factory glue for the bundled libwebp (webpxmux) WASM backend.
// The `.js` glue and `.wasm` binary are vendored from the MIT-licensed `webpxmux`
// package (which embeds BSD-licensed libwebp). See LICENSE-libwebp.

declare module 'external:emscripten/webp/webpxmux.js' {
    export default WEBPXMUX;
}

// tslint:disable
declare function WEBPXMUX (moduleOptions?: any): Promise<any>;
