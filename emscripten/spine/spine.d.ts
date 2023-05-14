declare module 'external:emscripten/spine/spine.asm.js' {
    export default SpineWasm;
}

declare function SpineWasm (moduleOptions?: any): Promise<void>;

declare namespace SpineWasm {
    type ptr = number;
    interface instance {
        spineWasmInstanceInit(): number;
        spineWasmInstanceDestroy(): number;
        queryStoreMemory(): ptr;
        createSkeletonObject (): ptr;
        setSkeletonData(objPtr: ptr, datPtr: ptr);
        setAnimation(objPtr: ptr, length: number, trackIndex: number, loop: boolean): boolean;
        clearTrack(objPtr: ptr, trackIndex: number): void;
        clearTracks(objPtr: ptr): void;
        setToSetupPose(objPtr: ptr): void;
        setSlotsToSetupPose(objPtr: ptr): void;
        setBonesToSetupPose(objPtr: ptr): void;
        setTimeScale(objPtr: ptr, timeScale: number): number;
        setSkin(objPtr: ptr, length: number): number;
        updateAnimation(objPtr: ptr, dltTime: number): number;
        setMix(objPtr: ptr, start: number, fromLength: number, toLength: number, duration: number);
        setAttachment(objPtr: ptr, start: number, length1: number, length2: number);
        updateRenderData(objPtr: ptr): number;
        getDrawOrderSize(objPtr: ptr): number;
        getSlotNameByOrder(objPtr: ptr, index: number): number;
        getBoneMatrix(objPtr: ptr, index: number): number;
        queryMemory(size: number): number;
        freeMemory(data: ptr);
        setDefaultScale(objPtr: ptr, scale: number): boolean;
        setVertexEffect(objPtr: ptr, effect: number, effectType: number);
        setPremultipliedAlpha(objPtr: ptr, premultipliedAlpha: boolean);
        setColor(objPtr: ptr, r: number, g: number, b: number, a: number);
        destroyInstance(objPtr: ptr);
        retainSkeletonDataByUUID(length: number): number;
        initSkeletonData(length: number, isJosn: boolean): number;
        recordSkeletonDataUUID(length: number, datPtr: number);
        createJitterVertexEffect(x: number, y: number): number;
        updateJitterParameters(handle: number, x: number, y: number);
        createSwirlVertexEffect(radius: number, power: number, usePowerOut: boolean): number;
        updateSwirlParameters(handle: number, centerX: number, centerY: number, radius: number, angle: number);
        memory: any;
    }
}
