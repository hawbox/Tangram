
WebRuntimeForVSps.dll: dlldata.obj WebRuntimeForVS_p.obj WebRuntimeForVS_i.obj
	link /dll /out:WebRuntimeForVSps.dll /def:WebRuntimeForVSps.def /entry:DllMain dlldata.obj WebRuntimeForVS_p.obj WebRuntimeForVS_i.obj \
		kernel32.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \
.c.obj:
	cl /c /Ox /DREGISTER_PROXY_DLL \
		$<

clean:
	@del WebRuntimeForVSps.dll
	@del WebRuntimeForVSps.lib
	@del WebRuntimeForVSps.exp
	@del dlldata.obj
	@del WebRuntimeForVS_p.obj
	@del WebRuntimeForVS_i.obj
