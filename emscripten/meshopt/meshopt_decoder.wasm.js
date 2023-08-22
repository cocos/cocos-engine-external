// This file is part of meshoptimizer library and is distributed under the terms of MIT License.
// Copyright (C) 2016-2023, by Arseny Kapoulkine (arseny.kapoulkine@gmail.com)
var MeshoptDecoder = (function() {
	"use strict";

	// Built with clang version 16.0.0
	// Built from meshoptimizer 0.19
	var wasm = "b9H79TebbbeYl9Gbb9Gvuuuuueu9Geueu9Giuuueuirobeediiviebeoweuec:q;iekr9Evo9TW9T9VV95dbH9F9F939H79T9F9J9H229F9Jt9VV7bb8A9TW79O9V9Wt9F9KW9J9V9KW9wWVtW949c919M9MWVbeY9TW79O9V9Wt9F9KW9J9V9KW69U9KW949c919M9MWVbdl79IV9Rbiq;08Kodbk:yzeHu8Jjjjjbcj;eb9Rgv8Kjjjjbc9:hodnadcefal0mbcuhoaiRbbc:Ge9hmbavaialfgrad9Radz:ejjjbhwcj;abad9UhlaicefhodnadTmbalc;WFbGglcjdalcjd6EhDcbhqinaqae9pmeaDaeaq9RaqaDfae6Egkcsfglcl4cifcd4hxdndndndnalc9WGgmTmbcbhPcehsawcjdfhzaohHinaraH9Rax6midnaraHaxfgo9RcK6mbczhlcbhOinalgic9WfgAawcj;cbffhldndndndndnaHaAco4fRbbaOcoG4ciGPlbedibkal9cb83ibalcwf9cb83ibxikalaoRblaoRbbgAco4gCaCciSgCE86bbawcj;cbfaifglcGfaoclfaCfgCRbbaAcl4ciGgXaXciSgXE86bbalcVfaCaXfgCRbbaAcd4ciGgXaXciSgXE86bbalc7faCaXfgCRbbaAciGgAaAciSgAE86bbalctfaCaAfgCRbbaoRbegAco4gXaXciSgXE86bbalc91faCaXfgCRbbaAcl4ciGgXaXciSgXE86bbalc4faCaXfgCRbbaAcd4ciGgXaXciSgXE86bbalc93faCaXfgCRbbaAciGgAaAciSgAE86bbalc94faCaAfgCRbbaoRbdgAco4gXaXciSgXE86bbalc95faCaXfgCRbbaAcl4ciGgXaXciSgXE86bbalc96faCaXfgCRbbaAcd4ciGgXaXciSgXE86bbalc97faCaXfgCRbbaAciGgAaAciSgAE86bbalc98faCaAfgARbbaoRbigoco4gCaCciSgCE86bbalc99faAaCfgARbbaocl4ciGgCaCciSgCE86bbalc9:faAaCfgARbbaocd4ciGgCaCciSgCE86bbalcufaAaCfglRbbaociGgoaociSgoE86bbalaofhoxdkalaoRbwaoRbbgAcl4gCaCcsSgCE86bbawcj;cbfaifglcGfaocwfaCfgCRbbaAcsGgAaAcsSgAE86bbalcVfaCaAfgARbbaoRbegCcl4gXaXcsSgXE86bbalc7faAaXfgARbbaCcsGgCaCcsSgCE86bbalctfaAaCfgARbbaoRbdgCcl4gXaXcsSgXE86bbalc91faAaXfgARbbaCcsGgCaCcsSgCE86bbalc4faAaCfgARbbaoRbigCcl4gXaXcsSgXE86bbalc93faAaXfgARbbaCcsGgCaCcsSgCE86bbalc94faAaCfgARbbaoRblgCcl4gXaXcsSgXE86bbalc95faAaXfgARbbaCcsGgCaCcsSgCE86bbalc96faAaCfgARbbaoRbvgCcl4gXaXcsSgXE86bbalc97faAaXfgARbbaCcsGgCaCcsSgCE86bbalc98faAaCfgARbbaoRbogCcl4gXaXcsSgXE86bbalc99faAaXfgARbbaCcsGgCaCcsSgCE86bbalc9:faAaCfgARbbaoRbrgocl4gCaCcsSgCE86bbalcufaAaCfglRbbaocsGgoaocsSgoE86bbalaofhoxekalao8Pbb83bbalcwfaocwf8Pbb83bbaoczfhokdnaiam9pmbaOcdfhOaiczfhlarao9RcL0mekkaiam6miaoTmidnakTmbawaPfRbbhOawcj;cbfhlazhiakhAinaialRbbgHce4cbaHceG9R7aOfgO86bbaiadfhialcefhlaAcufgAmbkkazcefhzaPcefgPad6hsaohHaPad9hmexvkkcbhoasceGmdxikaoaxad2fhXdnakTmbcbhmcehsawcjdfhCinarao9Rax6miaoTmdaoaxfhoawamfRbbhOawcj;cbfhlaChiakhAinaialRbbgHce4cbaHceG9R7aOfgO86bbaiadfhialcefhlaAcufgAmbkaCcefhCamcefgmad6hsamad9hmbkaXhoxikcbhlcehsinarao9Rax6mdaoTmeaoaxfhoalcefglad6hsadal9hmbkaXhoxdkcbhoasceGTmekc9:hoxikabaqad2fawcjdfakad2z:ejjjb8Aawawcjdfakcufad2fadz:ejjjb8Aakaqfhqaombkc9:hoxekcbc99arao9Radcaadca0ESEhokavcj;ebf8Kjjjjbaok;xzeHu8Jjjjjbc;ae9Rgv8Kjjjjbc9:hodnaeci9UgrcHfal0mbcuhoaiRbbgwc;WeGc;Ge9hmbawcsGgDce0mbavc;abfcFecjez:fjjjb8AavcUf9cu83ibavc8Wf9cu83ibavcyf9cu83ibavcaf9cu83ibavcKf9cu83ibavczf9cu83ibav9cu83iwav9cu83ibaialfc9WfhqaicefgwarfhodnaeTmbcmcsaDceSEhkcbhxcbhmcbhrcbhicbhlindnaoaq9nmbc9:hoxikdndnawRbbgDc;Ve0mbavc;abfalaDcu7gPcl4fcsGcitfgsydlhzasydbhHdnaDcsGgDak9pmbavaiaPfcsGcdtfydbaxaDEhsaDThDdndnadcd9hmbabarcetfgPaH87ebaPcdfaz87ebaPclfas87ebxekabarcdtfgPaHBdbaPclfazBdbaPcwfasBdbkaxaDfhxavc;abfalcitfgPasBdbaPazBdlavaicdtfasBdbavc;abfalcefcsGglcitfgPaHBdbaPasBdlaiaDfhialcefhlxdkdndnaDcsSmbamaDfaDc987fcefhmxekaocefhDao8SbbgscFeGhPdndnascu9mmbaDhoxekaocvfhoaPcFbGhPcrhsdninaD8SbbgOcFbGastaPVhPaOcu9kmeaDcefhDascrfgsc8J9hmbxdkkaDcefhokaPce4cbaPceG9R7amfhmkdndnadcd9hmbabarcetfgDaH87ebaDcdfaz87ebaDclfam87ebxekabarcdtfgDaHBdbaDclfazBdbaDcwfamBdbkavc;abfalcitfgDamBdbaDazBdlavaicdtfamBdbavc;abfalcefcsGglcitfgDaHBdbaDamBdlaicefhialcefhlxekdnaDcpe0mbaxcefgOavaiaqaDcsGfRbbgscl49RcsGcdtfydbascz6gPEhDavaias9RcsGcdtfydbaOaPfgzascsGgOEhsaOThOdndnadcd9hmbabarcetfgHax87ebaHcdfaD87ebaHclfas87ebxekabarcdtfgHaxBdbaHclfaDBdbaHcwfasBdbkavaicdtfaxBdbavc;abfalcitfgHaDBdbaHaxBdlavaicefgicsGcdtfaDBdbavc;abfalcefcsGcitfgHasBdbaHaDBdlavaiaPfcsGgicdtfasBdbavc;abfalcdfcsGglcitfgDaxBdbaDasBdlalcefhlaiaOfhiazaOfhxxekaxcbaoRbbgHEgAaDc;:eSgDfhzaHcsGhCaHcl4hXdndnaHcs0mbazcefhOxekazhOavaiaX9RcsGcdtfydbhzkdndnaCmbaOcefhxxekaOhxavaiaH9RcsGcdtfydbhOkdndnaDTmbaocefhDxekaocdfhDao8SbegPcFeGhsdnaPcu9kmbaocofhAascFbGhscrhodninaD8SbbgPcFbGaotasVhsaPcu9kmeaDcefhDaocrfgoc8J9hmbkaAhDxekaDcefhDkasce4cbasceG9R7amfgmhAkdndnaXcsSmbaDhsxekaDcefhsaD8SbbgocFeGhPdnaocu9kmbaDcvfhzaPcFbGhPcrhodninas8SbbgDcFbGaotaPVhPaDcu9kmeascefhsaocrfgoc8J9hmbkazhsxekascefhskaPce4cbaPceG9R7amfgmhzkdndnaCcsSmbashoxekascefhoas8SbbgDcFeGhPdnaDcu9kmbascvfhOaPcFbGhPcrhDdninao8SbbgscFbGaDtaPVhPascu9kmeaocefhoaDcrfgDc8J9hmbkaOhoxekaocefhokaPce4cbaPceG9R7amfgmhOkdndnadcd9hmbabarcetfgDaA87ebaDcdfaz87ebaDclfaO87ebxekabarcdtfgDaABdbaDclfazBdbaDcwfaOBdbkavc;abfalcitfgDazBdbaDaABdlavaicdtfaABdbavc;abfalcefcsGcitfgDaOBdbaDazBdlavaicefgicsGcdtfazBdbavc;abfalcdfcsGcitfgDaABdbaDaOBdlavaiaHcz6aXcsSVfgicsGcdtfaOBdbaiaCTaCcsSVfhialcifhlkawcefhwalcsGhlaicsGhiarcifgrae6mbkkcbc99aoaqSEhokavc;aef8Kjjjjbaok9teiucbcbydj1jjbgeabcifc98GfgbBdj1jjbdndnabZbcztgd9nmbcuhiabad9RcFFifcz4nbcuSmekaehikaik;LeeeudndnaeabVciGTmbabhixekdndnadcz9pmbabhixekabhiinaiaeydbBdbaiclfaeclfydbBdbaicwfaecwfydbBdbaicxfaecxfydbBdbaeczfheaiczfhiadc9Wfgdcs0mbkkadcl6mbinaiaeydbBdbaeclfheaiclfhiadc98fgdci0mbkkdnadTmbinaiaeRbb86bbaicefhiaecefheadcufgdmbkkabk;aeedudndnabciGTmbabhixekaecFeGc:b:c:ew2hldndnadcz9pmbabhixekabhiinaialBdbaicxfalBdbaicwfalBdbaiclfalBdbaiczfhiadc9Wfgdcs0mbkkadcl6mbinaialBdbaiclfhiadc98fgdci0mbkkdnadTmbinaiae86bbaicefhiadcufgdmbkkabkkkebcjwklz9Kbb";
	var wasmpack = new Uint8Array([32,0,65,2,1,106,34,33,3,128,11,4,13,64,6,253,10,7,15,116,127,5,8,12,40,16,19,54,20,9,27,255,113,17,42,67,24,23,146,148,18,14,22,45,70,69,56,114,101,21,25,63,75,136,108,28,118,29,73,115]);

	if (typeof WebAssembly !== 'object') {
		return {
			supported: false,
		};
	}

	var instance;

	var ready =
		WebAssembly.instantiate(unpack(wasm), {})
		.then(function(result) {
			instance = result.instance;
			instance.exports.__wasm_call_ctors();
		});

	function unpack(data) {
		var result = new Uint8Array(data.length);
		for (var i = 0; i < data.length; ++i) {
			var ch = data.charCodeAt(i);
			result[i] = ch > 96 ? ch - 97 : ch > 64 ? ch - 39 : ch + 4;
		}
		var write = 0;
		for (var i = 0; i < data.length; ++i) {
			result[write++] = (result[i] < 60) ? wasmpack[result[i]] : (result[i] - 60) * 64 + result[++i];
		}
		return result.buffer.slice(0, write);
	}

	function decode(fun, target, count, size, source, filter) {
		var sbrk = instance.exports.sbrk;
		var count4 = (count + 3) & ~3;
		var tp = sbrk(count4 * size);
		var sp = sbrk(source.length);
		var heap = new Uint8Array(instance.exports.memory.buffer);
		heap.set(source, sp);
		var res = fun(tp, count, size, sp, source.length);
		if (res == 0 && filter) {
			filter(tp, count4, size);
		}
		target.set(heap.subarray(tp, tp + count * size));
		sbrk(tp - sbrk(0));
		if (res != 0) {
			throw new Error("Malformed buffer data: " + res);
		}
	}

	var filters = {
		NONE: "",
		OCTAHEDRAL: "meshopt_decodeFilterOct",
		QUATERNION: "meshopt_decodeFilterQuat",
		EXPONENTIAL: "meshopt_decodeFilterExp",
	};

	var decoders = {
		ATTRIBUTES: "meshopt_decodeVertexBuffer",
		TRIANGLES: "meshopt_decodeIndexBuffer",
		INDICES: "meshopt_decodeIndexSequence",
	};

	var workers = [];
	var requestId = 0;

	function createWorker(url) {
		var worker = {
			object: new Worker(url),
			pending: 0,
			requests: {}
		};

		worker.object.onmessage = function(event) {
			var data = event.data;

			worker.pending -= data.count;
			worker.requests[data.id][data.action](data.value);

			delete worker.requests[data.id];
		};

		return worker;
	}

	function initWorkers(count) {
		var source =
			"var instance; var ready = WebAssembly.instantiate(new Uint8Array([" + new Uint8Array(unpack(wasm)) + "]), {})" +
			".then(function(result) { instance = result.instance; instance.exports.__wasm_call_ctors(); });" +
			"self.onmessage = workerProcess;" +
			decode.toString() + workerProcess.toString();

		var blob = new Blob([source], {type: 'text/javascript'});
		var url = URL.createObjectURL(blob);

		for (var i = 0; i < count; ++i) {
			workers[i] = createWorker(url);
		}

		URL.revokeObjectURL(url);
	}

	function decodeWorker(count, size, source, mode, filter) {
		var worker = workers[0];

		for (var i = 1; i < workers.length; ++i) {
			if (workers[i].pending < worker.pending) {
				worker = workers[i];
			}
		}

		return new Promise(function (resolve, reject) {
			var data = new Uint8Array(source);
			var id = requestId++;

			worker.pending += count;
			worker.requests[id] = { resolve: resolve, reject: reject };
			worker.object.postMessage({ id: id, count: count, size: size, source: data, mode: mode, filter: filter }, [ data.buffer ]);
		});
	}

	function workerProcess(event) {
		ready.then(function() {
			var data = event.data;
			try {
				var target = new Uint8Array(data.count * data.size);
				decode(instance.exports[data.mode], target, data.count, data.size, data.source, instance.exports[data.filter]);
				self.postMessage({ id: data.id, count: data.count, action: "resolve", value: target }, [ target.buffer ]);
			} catch (error) {
				self.postMessage({ id: data.id, count: data.count, action: "reject", value: error });
			}
		});
	}

	return {
		ready: ready,
		supported: true,
		useWorkers: function(count) {
			initWorkers(count);
		},
		decodeVertexBuffer: function(target, count, size, source, filter) {
			decode(instance.exports.meshopt_decodeVertexBuffer, target, count, size, source, instance.exports[filters[filter]]);
		},
		decodeIndexBuffer: function(target, count, size, source) {
			decode(instance.exports.meshopt_decodeIndexBuffer, target, count, size, source);
		},
		decodeIndexSequence: function(target, count, size, source) {
			decode(instance.exports.meshopt_decodeIndexSequence, target, count, size, source);
		},
		decodeGltfBuffer: function(target, count, size, source, mode, filter) {
			decode(instance.exports[decoders[mode]], target, count, size, source, instance.exports[filters[filter]]);
		},
		decodeGltfBufferAsync: function(count, size, source, mode, filter) {
			if (workers.length > 0) {
				return decodeWorker(count, size, source, decoders[mode], filters[filter]);
			}

			return ready.then(function() {
				var target = new Uint8Array(count * size);
				decode(instance.exports[decoders[mode]], target, count, size, source, instance.exports[filters[filter]]);
				return target;
			});
		}
	};
})();

export default MeshoptDecoder;