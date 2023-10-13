declare module 'external:emscripten/bullet/bullet.release.asm.js' {
    export default Bullet;
}

declare module 'external:emscripten/bullet/bullet.release.wasm.js' {
    export default Bullet;
}

// tslint:disable
declare function Bullet (moduleOptions?: any): Promise<void>;

declare namespace Bullet {
    type ptr = number;
    interface instance {
        HEAP8: Int8Array;
        HEAP16: Int16Array;
        HEAP32: Int32Array;
        HEAPU8: Uint8Array;
        HEAPU16: Uint16Array;
        HEAPU32: Uint32Array;
        HEAPF32: Float32Array;
        HEAPF64: Float64Array;

        // class interface
        DebugDraw: any;
        ControllerHitReport: any;
        MotionState: any;

        _malloc(bytes: number): ptr;
        _free(p: ptr): void;
        _read_f32(p: ptr): void;
        _write_f32(p: ptr, v: number): void;
        _safe_delete(p: ptr, bulletType: number): void;

        Vec3_new(x: number, y: number, z: number): ptr;
        Vec3_x(p: ptr): number;
        Vec3_y(p: ptr): number;
        Vec3_z(p: ptr): number;
        Vec3_set(p: ptr, x: number, y: number, z: number): void;

        Quat_new(x: number, y: number, z: number, w: number): ptr;
        Quat_x(p: ptr): number;
        Quat_y(p: ptr): number;
        Quat_z(p: ptr): number;
        Quat_w(p: ptr): number;
        Quat_set(p: ptr, x: number, y: number, z: number, w: number): void;

        Transform_new(): ptr;
        Transform_setIdentity(p: ptr): void;
        Transform_getOrigin(p: ptr): ptr;
        Transform_setRotation(p: ptr, quate: ptr): void;
        Transform_getRotation(p: ptr, quate: ptr): void;

        MotionState_getWorldTransform(p: ptr, transform: ptr): void;
        MotionState_setWorldTransform(p: ptr, transform: ptr): void;
        ccMotionState_new(id: number, initTrans: ptr): ptr;
        ccMotionState_setup(p: ptr, id: number, initTrans: ptr): void;

        int_array_size(p: ptr): number;
        int_array_at(p: ptr, index: number): number;
        Vec3_array_at(p: ptr, index: number): ptr;

        // constraints

        TypedConstraint_getFixedBody(): ptr;
        TypedConstraint_getDbgDrawSize(): number;
        TypedConstraint_setDbgDrawSize(p: ptr, dbgDrawSize: number): void;
        HingeConstraint_new(ptr0: ptr, ptr1: ptr, ptr2: ptr, ptr3: ptr): ptr;
        HingeConstraint_setFrames(ptr0: ptr, ptr1: ptr, ptr2: ptr): void;
        HingeConstraint_setLimit(p: ptr, low: number, upper: number, softness: number, biasFactor: number, relaxationFactor: number): void;
        HingeConstraint_setAngularOnly(p: ptr, angular: number): void;
        HingeConstraint_enableMotor(p: ptr, enable: boolean): void;
        HingeConstraint_setMotorVelocity(p: ptr, velocity: number): void;
        HingeConstraint_setMaxMotorImpulse(p: ptr, maxImpulse: number): void;
        HingeConstraint_setMotorTarget(p: ptr, target: number, dt: number): void;
        P2PConstraint_new(ptr0: ptr, ptr1: ptr, ptr2: ptr, ptr3: ptr): ptr;
        P2PConstraint_setPivotA(ptr0: ptr, ptr1: ptr): void;
        P2PConstraint_setPivotB(ptr0: ptr, ptr1: ptr): void;
        TypedConstraint_setMaxImpulseThreshold(ptr0: ptr, maxImpulse: number): void;
        FixedConstraint_new(ptr0: ptr, ptr1: ptr, ptr2: ptr, ptr3: ptr): ptr;
        FixedConstraint_setFrames(ptr0: ptr, ptr1: ptr, ptr2: ptr): void;
        Generic6DofSpring2Constraint_new(ptr0: ptr, ptr1: ptr, ptr2: ptr, ptr3: ptr, rotateOrder: number): ptr;
        Generic6DofSpring2Constraint_setFrames(ptr0: ptr, ptr1: ptr, ptr2: ptr): void;
        Generic6DofSpring2Constraint_setLimit(ptr0: ptr, index: number, lo: number, hi: number): void;
        Generic6DofSpring2Constraint_enableSpring(ptr0: ptr, index: number, onOff: boolean): void;
        Generic6DofSpring2Constraint_setStiffness(ptr0: ptr, index: number, stiffness: number): void;
        Generic6DofSpring2Constraint_setDamping(ptr0: ptr, index: number, damping: number): void;
        Generic6DofSpring2Constraint_setBounce(ptr0: ptr, index: number, bounce: number): void;
        Generic6DofSpring2Constraint_setEquilibriumPoint(ptr0: ptr, index: number, val: number): void;
        Generic6DofSpring2Constraint_enableMotor(ptr0: ptr, index: number, onOff: boolean): void;
        Generic6DofSpring2Constraint_setMaxMotorForce(ptr0: ptr, index: number, force: number): void;
        Generic6DofSpring2Constraint_setTargetVelocity(ptr0: ptr, index: number, velocity: number): void;
        Generic6DofSpring2Constraint_setServo(ptr0: ptr, index: number, onOff: boolean): number;
        Generic6DofSpring2Constraint_setServoTarget(ptr0: ptr, index: number, target: number): number;

        // shapes

        // CollisionShape_getUserIndex(p: ptr): number;
        // CollisionShape_setUserIndex(p: ptr, i: number): void;
        CollisionShape_isCompound(p: ptr): boolean;
        CollisionShape_setLocalScaling(p: ptr, scale: ptr): void;
        CollisionShape_calculateLocalInertia(p: ptr, mass: number, localInertia: ptr): void;
        CollisionShape_getAabb(p: ptr, t: ptr, min: ptr, max: ptr): void;
        CollisionShape_getLocalBoundingSphere(p: ptr): number;
        CollisionShape_setMargin(p: ptr, margin: number): void;
        CollisionShape_setMaterial(p: ptr, mat: ptr): void;
        CollisionShape_setUserPointer(p: ptr, p0: ptr): void;

        EmptyShape_static(): ptr;

        ConvexInternalShape_getImplicitShapeDimensions(p: ptr): ptr;

        BoxShape_new(p: ptr): ptr;
        BoxShape_setUnscaledHalfExtents(p: ptr, halfExtents: ptr): void;

        SphereShape_new(radius: number): ptr;
        SphereShape_setUnscaledRadius(p: ptr, radius: number): void;

        CylinderShape_new(halfExtents: ptr): ptr;
        CylinderShape_updateProp(p: ptr, r: number, g: number, d: number): void;

        CapsuleShape_new(radius: number, height: number): ptr;
        CapsuleShape_updateProp(p: ptr, r: number, g: number, d: number): void;

        ConeShape_new(radius: number, height: number): ptr;
        ConeShape_setRadius(p: ptr, v: number): void;
        ConeShape_setHeight(p: ptr, v: number): void;
        ConeShape_setConeUpIndex(p: ptr, v: number): void;

        StaticPlaneShape_new(normal: ptr, constant: number): ptr;
        StaticPlaneShape_getPlaneNormal(p: ptr): ptr;
        StaticPlaneShape_setPlaneConstant(p: ptr, constant: number): void;

        TerrainShape_new(i: number, j: number, p: ptr, hs: number, min: number, max: number): ptr;

        TriangleMesh_new(): ptr;
        TriangleMesh_addTriangle(p: ptr, v0: ptr, v1: ptr, v2: ptr, removeDuplicateVertices: boolean): void;
        BvhTriangleMeshShape_new(p: ptr, c: boolean, bvh: boolean): ptr;
        BvhTriangleMeshShape_getOptimizedBvh(p: ptr): ptr;
        BvhTriangleMeshShape_setOptimizedBvh(p: ptr, p1: ptr, scaleX: number, scaleY: number, scaleZ: number);
        ScaledBvhTriangleMeshShape_new(p: ptr, scaleX: number, scaleY: number, scaleZ: number): ptr;
        ConvexTriangleMeshShape_new(p: ptr): ptr;

        SimplexShape_new(): ptr;
        SimplexShape_addVertex(p: ptr, pt: ptr): void;

        ccCompoundShape_new(): ptr;
        CompoundShape_getNumChildShapes(p: ptr): number;
        CompoundShape_getChildShape(p: ptr, i: number): ptr;
        CompoundShape_addChildShape(p: ptr, local: ptr, shape: ptr): void;
        CompoundShape_removeChildShape(p: ptr, shape: ptr): void;
        CompoundShape_updateChildTransform(p: ptr, i: number, trans: ptr, shouldRecalculateLocalAabb: boolean): void;
        CompoundShape_setMaterial(p: ptr, i: number, f: number, r: number, rf: number, sf: number): void;

        // collision

        CollisionObject_new(): number;
        CollisionObject_getCollisionShape(p: ptr): ptr;
        CollisionObject_setContactProcessingThreshold(p: ptr, contactProcessingThreshold: number): void;
        CollisionObject_getActivationState(p: ptr): number;
        CollisionObject_setActivationState(p: ptr, newState: number): void;
        CollisionObject_forceActivationState(p: ptr, newState: number): void;
        CollisionObject_activate(p: ptr, forceActivation?: boolean): void;
        CollisionObject_isActive(p: ptr): boolean;
        CollisionObject_isKinematicObject(p: ptr): boolean;
        CollisionObject_isStaticObject(p: ptr): boolean;
        CollisionObject_isStaticOrKinematicObject(p: ptr): boolean;
        CollisionObject_isSleeping(p: ptr): boolean;
        CollisionObject_getWorldTransform(p: ptr): ptr;
        CollisionObject_getCollisionFlags(p: ptr): number;
        CollisionObject_setCollisionFlags(p: ptr, flags: number): void;
        CollisionObject_setWorldTransform(p: ptr, transform: ptr): void;
        CollisionObject_setCollisionShape(p: ptr, shape: ptr): void;
        CollisionObject_setCcdMotionThreshold(p: ptr, ccdMotionThreshold: number): void;
        CollisionObject_setCcdSweptSphereRadius(p: ptr, radius: number): void;
        CollisionObject_getUserIndex(p: ptr): number;
        CollisionObject_setUserIndex(p: ptr, index: number): void;
        CollisionObject_getUserPointer(p: ptr): number;
        CollisionObject_setUserPointer(p: ptr, userPointer: number): void;
        CollisionObject_setMaterial(p: ptr, f: number, r: number, rf: number, sf: number): void;
        CollisionObject_setIgnoreCollisionCheck(p: ptr, p0: ptr, v: boolean): void;

        RigidBody_new(m: number, ms: number): ptr;
        RigidBody_getFlags(p: ptr): number;
        RigidBody_setFlags(p: ptr, flags: number): void;
        RigidBody_setGravity(p: ptr, g: ptr): number;
        RigidBody_setDamping(p: ptr, lin: number, ang: number): void;
        RigidBody_setMass(p: ptr, m: number);
        RigidBody_setMassProps(p: ptr, m: number, localInertia: ptr): void;
        RigidBody_setLinearFactor(p: ptr, f: ptr): number;
        RigidBody_setAngularFactor(p: ptr, f: ptr): number;
        RigidBody_getLinearVelocity(p: ptr): ptr;
        RigidBody_getAngularVelocity(p: ptr): ptr;
        RigidBody_setLinearVelocity(p: ptr, v: ptr): void;
        RigidBody_setAngularVelocity(p: ptr, v: ptr): void;
        RigidBody_clearState(p: ptr): void;
        RigidBody_clearForces(p: ptr): void;
        RigidBody_wantsSleeping(p: ptr): boolean;
        RigidBody_setSleepingThresholds(p: ptr, linear: number, angular: number): void;
        RigidBody_getLinearSleepingThreshold(p: ptr): number;
        RigidBody_getMotionState(p: ptr): ptr;
        RigidBody_applyTorque(p: ptr, f: ptr): void;
        RigidBody_applyForce(p: ptr, f: ptr, rp: ptr): void;
        RigidBody_applyImpulse(p: ptr, f: ptr, rp: ptr): void;
        RigidBody_getWorldTransform(p: ptr, transform: ptr): void;
        Transform_getRotationAndOrigin(transform: ptr, q: ptr): ptr;

        // dynamic

        DefaultCollisionConfiguration_static(): ptr;
        CollisionDispatcher_new(): ptr;
        Dispatcher_getNumManifolds(p: ptr): number;
        Dispatcher_getManifoldByIndexInternal(p: ptr, i: number): ptr;

        ManifoldPoint_getShape0(p: ptr): ptr;
        ManifoldPoint_getShape1(p: ptr): ptr;
        ManifoldPoint_get_m_index0(p: ptr): number;
        ManifoldPoint_get_m_index1(p: ptr): number;
        PersistentManifold_getBody0(p: ptr): ptr;
        PersistentManifold_getBody1(p: ptr): ptr;
        PersistentManifold_getNumContacts(p: ptr): number;
        PersistentManifold_getContactPoint(p: ptr, i: number): ptr;
        ManifoldPoint_get_m_localPointA(p: ptr): ptr;
        ManifoldPoint_get_m_localPointB(p: ptr): ptr;
        ManifoldPoint_get_m_positionWorldOnA(p: ptr): ptr;
        ManifoldPoint_get_m_positionWorldOnB(p: ptr): ptr;
        ManifoldPoint_get_m_normalWorldOnB(p: ptr): ptr;
        ManifoldPoint_get_m_positionWorldOnB(p: ptr): ptr;

        DbvtBroadphase_new(): ptr;
        SequentialImpulseConstraintSolver_new(): ptr;

        CollisionWorld_addCollisionObject(p: ptr, body: ptr, g: number, m: number): void;
        CollisionWorld_removeCollisionObject(p: ptr, body: ptr): void;
        CollisionWorld_rayTest(p: ptr, p0: ptr, p1: ptr, p2: ptr): void;
        CollisionWorld_convexSweepTest(p: ptr, castShape: ptr, from: ptr, to: ptr, resultCallback: ptr, allowedCcdPenetration: ptr): void;
        CollisionWorld_setDebugDrawer(p: ptr, drawer: ptr): void;
        CollisionWorld_debugDrawWorld(p: ptr): void;

        ccDiscreteDynamicsWorld_new(dispatcher: ptr, pairCache: ptr, solver: ptr): ptr;
        ccDiscreteDynamicsWorld_setAllowSleep(p: ptr, v: boolean): void;
        DynamicsWorld_setGravity(p: ptr, g: ptr): void;
        DynamicsWorld_stepSimulation(p: ptr, timeStep: number, maxSubSteps: number, fixedTimeStep: number): ptr;
        DynamicsWorld_addRigidBody(p: ptr, body: ptr, g: number, m: number): void;
        DynamicsWorld_removeRigidBody(p: ptr, body: ptr): void;
        DynamicsWorld_addConstraint(p: ptr, p2: ptr, v: boolean): void;
        DynamicsWorld_removeConstraint(p: ptr, p2: ptr): void;
        DynamicsWorld_addAction(p: ptr, action: ptr): void;
        DynamicsWorld_removeAction(p: ptr, action: ptr): void;

        DebugDraw_new(): ptr;
        DebugDraw_setDebugMode(p: ptr, debugMode: number): void;
        DebugDraw_getDebugMode(p: ptr): number;
        DebugDraw_setActiveObjectColor(p: ptr, r: number, g: number, b: number): void;
        DebugDraw_setDeactiveObjectColor(p: ptr, r: number, g: number, b: number): void;
        DebugDraw_setWantsDeactivationObjectColor(p: ptr, r: number, g: number, b: number): void;
        DebugDraw_setDisabledDeactivationObjectColor(p: ptr, r: number, g: number, b: number): void;
        DebugDraw_setDisabledSimulationObjectColor(p: ptr, r: number, g: number, b: number): void;
        DebugDraw_setAABBColor(p: ptr, r: number, g: number, b: number): void;
        DebugDraw_setContactPointColor(p: ptr, r: number, g: number, b: number): void;
        DebugDraw_setConstraintLimitColor(p: ptr, r: number, g: number, b: number): void;

        RayCallback_hasHit(p: ptr): boolean;
        ConvexCallback_hasHit(p: ptr): boolean;

        ccAllRayCallback_static(): ptr;
        ccAllRayCallback_setFlags(p: ptr, flag: number): void;
        ccAllRayCallback_reset(p: ptr, p0: ptr, p1: ptr, m: number, q: boolean): void;
        ccAllRayCallback_getHitPointWorld(p: ptr): ptr;
        ccAllRayCallback_getHitNormalWorld(p: ptr): ptr;
        ccAllRayCallback_getCollisionShapePtrs(p: ptr): ptr;

        ccClosestRayCallback_static(): ptr;
        ccClosestRayCallback_setFlags(p: ptr, flag: number): void;
        ccClosestRayCallback_reset(p: ptr, p0: ptr, p1: ptr, m: number, q: boolean): void;
        ccClosestRayCallback_getHitPointWorld(p: ptr): ptr;
        ccClosestRayCallback_getHitNormalWorld(p: ptr): ptr;
        ccClosestRayCallback_getCollisionShapePtr(p: ptr): ptr;

        ccAllConvexCallback_static(): ptr;
        ccAllConvexCallback_reset(p: ptr, p0: ptr, p1: ptr, m: number, q: boolean): void;
        ccAllConvexCallback_getHitPointWorld(p: ptr): ptr;
        ccAllConvexCallback_getHitNormalWorld(p: ptr): ptr;
        ccAllConvexCallback_getCollisionShapePtrs(p: ptr): ptr;

        ccClosestConvexCallback_static(): ptr;
        ccClosestConvexCallback_reset(p: ptr, p0: ptr, p1: ptr, m: number, q: boolean): void;
        ccClosestConvexCallback_getHitPointWorld(p: ptr): ptr;
        ccClosestConvexCallback_getHitNormalWorld(p: ptr): ptr;
        ccClosestConvexCallback_getCollisionShapePtr(p: ptr): ptr;

        ccMaterial_new(): ptr;
        ccMaterial_set(p: ptr, r: number, f: number, rf: number, sf: number): void;

        // CharacterController
        ControllerHitReport_new(): ptr;
        CharacterController_getGhostObject(ptrCCT: ptr): ptr;
        CharacterController_getCollisionShape(ptrCCT: ptr): ptr;
        ControllerHit_getCurrentController(p: ptr): ptr;
        ControllerHit_getHitWorldPos(p: ptr): ptr;
        ControllerHit_getHitWorldNormal(p: ptr): ptr;
        ControllerHit_getHitMotionDir(p: ptr): ptr;         //CCT hit Motion direction
        ControllerHit_getHitMotionLength(p: ptr): number;   //CCT hit Motion length
        ControllerShapeHit_getHitShape(p: ptr): ptr;
        ControllerShapeHit_getHitCollisionObject(p: ptr): ptr;
        CharacterController_move(ptrCCT: ptr, ptrMovement: ptr, minDist: number, deltaTime: number): number;
        CharacterController_getPosition(ptrCCT: ptr);
        CharacterController_setContactOffset(ptrCCT: ptr, v: number);
        CharacterController_setStepOffset(ptrCCT: ptr, v: number);
        CharacterController_setSlopeLimit(ptrCCT: ptr, v: number);
        CharacterController_setCollision(ptrCCT: ptr, collision: boolean);
        CharacterController_setOverlapRecovery(ptrCCT: ptr, value: boolean);
        CapsuleCharacterControllerDesc_new(maxSlopeRadians: number, stepHeight: number, contactOffset: number,
            ptrUpAxis: ptr, ptrInitPos: ptr, ptruUserControllerHitReport: ptr, radius: number, height: number): ptr;
        CapsuleCharacterController_new(collisionWorld: ptr, ptrBtCapsuleCharacterControllerDesc: ptr, userObjectPointer: ptr): ptr;
        CapsuleCharacterController_setRadius(ptrCCT: ptr, radius: number): void;
        CapsuleCharacterController_setHeight(ptrCCT: ptr, height: number): void;
        BoxCharacterControllerDesc_new(maxSlopeRadians: number, stepHeight: number, contactOffset: number,
            ptrUpAxis: ptr, ptrInitPos: ptr, ptruUserControllerHitReport: ptr, halfHeight: number, halfSideExtent: number, halfForwardExtent: number): ptr;
        BoxCharacterController_new(collisionWorld: ptr, ptrBtBoxCharacterControllerDesc: ptr, userObjectPointer: ptr): ptr;
        BoxCharacterController_setHalfHeight(ptrCCT: ptr, v: number): void;
        BoxCharacterController_setHalfSideExtent(ptrCCT: ptr, v: number): void;
        BoxCharacterController_setHalfForwardExtent(ptrCCT: ptr, v: number): void;
    }
}
