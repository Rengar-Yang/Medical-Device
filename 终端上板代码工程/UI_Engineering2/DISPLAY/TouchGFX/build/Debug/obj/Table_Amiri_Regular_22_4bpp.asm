; Listing generated by Microsoft (R) Optimizing Compiler Version 19.30.30705.0 

	TITLE	D:\学习\毕业设计\方案1_GFX+底板\官方例程\DISPLAY\TouchGFX\build\Debug\obj\Table_Amiri_Regular_22_4bpp.obj
	.686P
	.XMM
	include listing.inc
	.model	flat

INCLUDELIB MSVCRTD
INCLUDELIB OLDNAMES

PUBLIC	?glyphs_Amiri_Regular_22_4bpp@@3QBUGlyphNode@touchgfx@@B ; glyphs_Amiri_Regular_22_4bpp
PUBLIC	?unicodes_Amiri_Regular_22_4bpp@@3QBQBEB	; unicodes_Amiri_Regular_22_4bpp
EXTRN	?unicodes_Amiri_Regular_22_4bpp_0@@3QBEB:BYTE	; unicodes_Amiri_Regular_22_4bpp_0
msvcjmc	SEGMENT
__692521D7_concurrencysal@h DB 01H
__A324AF7F_sal@h DB 01H
__3FA7CF14_vadefs@h DB 01H
__4DFECF8D_vcruntime@h DB 01H
__6569C2CA_corecrt@h DB 01H
__C3DF3361_assert@h DB 01H
__47AAA172_stdint@h DB 01H
__BA83647B_Config@hpp DB 01H
__AA120D12_Types@hpp DB 01H
__73751FBD_stdarg@h DB 01H
__249BB391_Unicode@hpp DB 01H
__2B5BEDA9_Font@hpp DB 01H
__66C3C840_ConstFont@hpp DB 01H
__9BA7F6D3_GeneratedFont@hpp DB 01H
__279C6AF9_Table_Amiri_Regular_22_4bpp@cpp DB 01H
msvcjmc	ENDS
CONST	SEGMENT
?glyphs_Amiri_Regular_22_4bpp@@3QBUGlyphNode@touchgfx@@B DD 00H ; glyphs_Amiri_Regular_22_4bpp
	DW	03fH
	DB	06H
	DB	0fH
	DB	0fH
	DB	01H
	DB	08H
	DB	00H
	DB	00H
	DB	00H
	ORG $+2
?unicodes_Amiri_Regular_22_4bpp@@3QBQBEB DD FLAT:?unicodes_Amiri_Regular_22_4bpp_0@@3QBEB ; unicodes_Amiri_Regular_22_4bpp
CONST	ENDS
PUBLIC	??1Font@touchgfx@@UAE@XZ			; touchgfx::Font::~Font
PUBLIC	?getGlyph@Font@touchgfx@@UBEPBUGlyphNode@2@G@Z	; touchgfx::Font::getGlyph
PUBLIC	?getFallbackChar@Font@touchgfx@@UBEGXZ		; touchgfx::Font::getFallbackChar
PUBLIC	?getEllipsisChar@Font@touchgfx@@UBEGXZ		; touchgfx::Font::getEllipsisChar
PUBLIC	?getFontHeight@Font@touchgfx@@UBEGXZ		; touchgfx::Font::getFontHeight
PUBLIC	?getMinimumTextHeight@Font@touchgfx@@UBEGXZ	; touchgfx::Font::getMinimumTextHeight
PUBLIC	?getBitsPerPixel@Font@touchgfx@@UBEEXZ		; touchgfx::Font::getBitsPerPixel
PUBLIC	?getByteAlignRow@Font@touchgfx@@UBEEXZ		; touchgfx::Font::getByteAlignRow
PUBLIC	?getKerning@Font@touchgfx@@UBECGPBUGlyphNode@2@@Z ; touchgfx::Font::getKerning
PUBLIC	?getGSUBTable@Font@touchgfx@@UBEPBGXZ		; touchgfx::Font::getGSUBTable
PUBLIC	?getContextualFormsTable@Font@touchgfx@@UBEPBUFontContextualFormsTable@2@XZ ; touchgfx::Font::getContextualFormsTable
PUBLIC	??_GFont@touchgfx@@UAEPAXI@Z			; touchgfx::Font::`scalar deleting destructor'
PUBLIC	??1ConstFont@touchgfx@@UAE@XZ			; touchgfx::ConstFont::~ConstFont
PUBLIC	??1GeneratedFont@touchgfx@@UAE@XZ		; touchgfx::GeneratedFont::~GeneratedFont
PUBLIC	?getFont_Amiri_Regular_22_4bpp@@YAAAVGeneratedFont@touchgfx@@XZ ; getFont_Amiri_Regular_22_4bpp
PUBLIC	__JustMyCode_Default
PUBLIC	??_7Font@touchgfx@@6B@				; touchgfx::Font::`vftable'
PUBLIC	??_R4Font@touchgfx@@6B@				; touchgfx::Font::`RTTI Complete Object Locator'
PUBLIC	??_R0?AVFont@touchgfx@@@8			; touchgfx::Font `RTTI Type Descriptor'
PUBLIC	??_R3Font@touchgfx@@8				; touchgfx::Font::`RTTI Class Hierarchy Descriptor'
PUBLIC	??_R2Font@touchgfx@@8				; touchgfx::Font::`RTTI Base Class Array'
PUBLIC	??_R1A@?0A@EA@Font@touchgfx@@8			; touchgfx::Font::`RTTI Base Class Descriptor at (0,-1,0,64)'
EXTRN	__purecall:PROC
EXTRN	??3@YAXPAXI@Z:PROC				; operator delete
EXTRN	_atexit:PROC
EXTRN	__Init_thread_header:PROC
EXTRN	__Init_thread_abort:PROC
EXTRN	__Init_thread_footer:PROC
EXTRN	?getStringWidth@Font@touchgfx@@UBAGPBGZZ:PROC	; touchgfx::Font::getStringWidth
EXTRN	?getStringWidth@Font@touchgfx@@UBAGEPBGZZ:PROC	; touchgfx::Font::getStringWidth
EXTRN	?getCharWidth@Font@touchgfx@@UBEGG@Z:PROC	; touchgfx::Font::getCharWidth
EXTRN	?getSpacingAbove@Font@touchgfx@@UBAEPBGZZ:PROC	; touchgfx::Font::getSpacingAbove
EXTRN	?getMaxTextHeight@Font@touchgfx@@UBAGPBGZZ:PROC	; touchgfx::Font::getMaxTextHeight
EXTRN	?getNumberOfLines@Font@touchgfx@@UBAGPBGZZ:PROC	; touchgfx::Font::getNumberOfLines
EXTRN	??_EFont@touchgfx@@UAEPAXI@Z:PROC		; touchgfx::Font::`vector deleting destructor'
EXTRN	??0GeneratedFont@touchgfx@@QAE@PBUGlyphNode@1@GGEEEEEPBQBEPBUKerningNode@1@GGQBGPBUFontContextualFormsTable@1@@Z:PROC ; touchgfx::GeneratedFont::GeneratedFont
EXTRN	@_RTC_CheckStackVars@8:PROC
EXTRN	@__CheckForDebuggerJustMyCode@4:PROC
EXTRN	@__security_check_cookie@4:PROC
EXTRN	__RTC_CheckEsp:PROC
EXTRN	__RTC_InitBase:PROC
EXTRN	__RTC_Shutdown:PROC
EXTRN	___CxxFrameHandler3:PROC
EXTRN	__Init_thread_epoch:DWORD
EXTRN	?kerning_Amiri_Regular_22_4bpp@@3QBUKerningNode@touchgfx@@B:BYTE ; kerning_Amiri_Regular_22_4bpp
EXTRN	?Amiri_Regular_contextualFormsTable@@3UFontContextualFormsTable@touchgfx@@B:BYTE ; Amiri_Regular_contextualFormsTable
EXTRN	??_7type_info@@6B@:QWORD			; type_info::`vftable'
EXTRN	___security_cookie:DWORD
EXTRN	__tls_array:DWORD
EXTRN	__tls_index:DWORD
_BSS	SEGMENT
?Amiri_Regular_22_4bpp@?1??getFont_Amiri_Regular_22_4bpp@@YAAAVGeneratedFont@touchgfx@@XZ@4V23@A DB 028H DUP (?) ; `getFont_Amiri_Regular_22_4bpp'::`2'::Amiri_Regular_22_4bpp
?$TSS0@?1??getFont_Amiri_Regular_22_4bpp@@YAAAVGeneratedFont@touchgfx@@XZ@4HA DD 01H DUP (?) ; `getFont_Amiri_Regular_22_4bpp'::`2'::$TSS0
_BSS	ENDS
;	COMDAT rtc$TMZ
rtc$TMZ	SEGMENT
__RTC_Shutdown.rtc$TMZ DD FLAT:__RTC_Shutdown
rtc$TMZ	ENDS
;	COMDAT rtc$IMZ
rtc$IMZ	SEGMENT
__RTC_InitBase.rtc$IMZ DD FLAT:__RTC_InitBase
rtc$IMZ	ENDS
;	COMDAT ??_R1A@?0A@EA@Font@touchgfx@@8
rdata$r	SEGMENT
??_R1A@?0A@EA@Font@touchgfx@@8 DD FLAT:??_R0?AVFont@touchgfx@@@8 ; touchgfx::Font::`RTTI Base Class Descriptor at (0,-1,0,64)'
	DD	00H
	DD	00H
	DD	0ffffffffH
	DD	00H
	DD	040H
	DD	FLAT:??_R3Font@touchgfx@@8
rdata$r	ENDS
;	COMDAT ??_R2Font@touchgfx@@8
rdata$r	SEGMENT
??_R2Font@touchgfx@@8 DD FLAT:??_R1A@?0A@EA@Font@touchgfx@@8 ; touchgfx::Font::`RTTI Base Class Array'
rdata$r	ENDS
;	COMDAT ??_R3Font@touchgfx@@8
rdata$r	SEGMENT
??_R3Font@touchgfx@@8 DD 00H				; touchgfx::Font::`RTTI Class Hierarchy Descriptor'
	DD	00H
	DD	01H
	DD	FLAT:??_R2Font@touchgfx@@8
rdata$r	ENDS
;	COMDAT ??_R0?AVFont@touchgfx@@@8
data$rs	SEGMENT
??_R0?AVFont@touchgfx@@@8 DD FLAT:??_7type_info@@6B@	; touchgfx::Font `RTTI Type Descriptor'
	DD	00H
	DB	'.?AVFont@touchgfx@@', 00H
data$rs	ENDS
;	COMDAT ??_R4Font@touchgfx@@6B@
rdata$r	SEGMENT
??_R4Font@touchgfx@@6B@ DD 00H				; touchgfx::Font::`RTTI Complete Object Locator'
	DD	00H
	DD	00H
	DD	FLAT:??_R0?AVFont@touchgfx@@@8
	DD	FLAT:??_R3Font@touchgfx@@8
rdata$r	ENDS
;	COMDAT ??_7Font@touchgfx@@6B@
CONST	SEGMENT
??_7Font@touchgfx@@6B@ DD FLAT:??_R4Font@touchgfx@@6B@	; touchgfx::Font::`vftable'
	DD	FLAT:??_EFont@touchgfx@@UAEPAXI@Z
	DD	FLAT:?getGlyph@Font@touchgfx@@UBEPBUGlyphNode@2@G@Z
	DD	FLAT:__purecall
	DD	FLAT:?getFallbackChar@Font@touchgfx@@UBEGXZ
	DD	FLAT:?getEllipsisChar@Font@touchgfx@@UBEGXZ
	DD	FLAT:?getStringWidth@Font@touchgfx@@UBAGEPBGZZ
	DD	FLAT:?getStringWidth@Font@touchgfx@@UBAGPBGZZ
	DD	FLAT:?getCharWidth@Font@touchgfx@@UBEGG@Z
	DD	FLAT:?getSpacingAbove@Font@touchgfx@@UBAEPBGZZ
	DD	FLAT:?getMaxTextHeight@Font@touchgfx@@UBAGPBGZZ
	DD	FLAT:?getFontHeight@Font@touchgfx@@UBEGXZ
	DD	FLAT:?getMinimumTextHeight@Font@touchgfx@@UBEGXZ
	DD	FLAT:?getBitsPerPixel@Font@touchgfx@@UBEEXZ
	DD	FLAT:?getByteAlignRow@Font@touchgfx@@UBEEXZ
	DD	FLAT:?getKerning@Font@touchgfx@@UBECGPBUGlyphNode@2@@Z
	DD	FLAT:?getNumberOfLines@Font@touchgfx@@UBAGPBGZZ
	DD	FLAT:?getGSUBTable@Font@touchgfx@@UBEPBGXZ
	DD	FLAT:?getContextualFormsTable@Font@touchgfx@@UBEPBUFontContextualFormsTable@2@XZ
CONST	ENDS
;	COMDAT voltbl
voltbl	SEGMENT
_volmd	DB	01aH
voltbl	ENDS
;	COMDAT xdata$x
xdata$x	SEGMENT
__unwindtable$?getFont_Amiri_Regular_22_4bpp@@YAAAVGeneratedFont@touchgfx@@XZ DD 0ffffffffH
	DD	FLAT:__unwindfunclet$?getFont_Amiri_Regular_22_4bpp@@YAAAVGeneratedFont@touchgfx@@XZ$0
__ehfuncinfo$?getFont_Amiri_Regular_22_4bpp@@YAAAVGeneratedFont@touchgfx@@XZ DD 019930522H
	DD	01H
	DD	FLAT:__unwindtable$?getFont_Amiri_Regular_22_4bpp@@YAAAVGeneratedFont@touchgfx@@XZ
	DD	2 DUP(00H)
	DD	2 DUP(00H)
	DD	00H
	DD	01H
xdata$x	ENDS
; Function compile flags: /Odt
;	COMDAT __JustMyCode_Default
_TEXT	SEGMENT
__JustMyCode_Default PROC				; COMDAT
	push	ebp
	mov	ebp, esp
	pop	ebp
	ret	0
__JustMyCode_Default ENDP
_TEXT	ENDS
; Function compile flags: /Odtp /RTCsu /ZI
;	COMDAT ??__FAmiri_Regular_22_4bpp@?1??getFont_Amiri_Regular_22_4bpp@@YAAAVGeneratedFont@touchgfx@@XZ@YAXXZ
text$yd	SEGMENT
??__FAmiri_Regular_22_4bpp@?1??getFont_Amiri_Regular_22_4bpp@@YAAAVGeneratedFont@touchgfx@@XZ@YAXXZ PROC ; `getFont_Amiri_Regular_22_4bpp'::`2'::`dynamic atexit destructor for 'Amiri_Regular_22_4bpp'', COMDAT
	push	ebp
	mov	ebp, esp
	sub	esp, 192				; 000000c0H
	push	ebx
	push	esi
	push	edi
	mov	edi, ebp
	xor	ecx, ecx
	mov	eax, -858993460				; ccccccccH
	rep stosd
	mov	ecx, OFFSET ?Amiri_Regular_22_4bpp@?1??getFont_Amiri_Regular_22_4bpp@@YAAAVGeneratedFont@touchgfx@@XZ@4V23@A
	call	??1GeneratedFont@touchgfx@@UAE@XZ
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 192				; 000000c0H
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	0
??__FAmiri_Regular_22_4bpp@?1??getFont_Amiri_Regular_22_4bpp@@YAAAVGeneratedFont@touchgfx@@XZ@YAXXZ ENDP ; `getFont_Amiri_Regular_22_4bpp'::`2'::`dynamic atexit destructor for 'Amiri_Regular_22_4bpp''
text$yd	ENDS
; Function compile flags: /Odtp /RTCsu /ZI
;	COMDAT ?getFont_Amiri_Regular_22_4bpp@@YAAAVGeneratedFont@touchgfx@@XZ
_TEXT	SEGMENT
__$EHRec$ = -12						; size = 12
?getFont_Amiri_Regular_22_4bpp@@YAAAVGeneratedFont@touchgfx@@XZ PROC ; getFont_Amiri_Regular_22_4bpp, COMDAT
; File D:\学习\毕业设计\方案1_GFX+底板\官方例程\DISPLAY\TouchGFX\generated\fonts\src\Table_Amiri_Regular_22_4bpp.cpp
; Line 25
	push	ebp
	mov	ebp, esp
	push	-1
	push	__ehhandler$?getFont_Amiri_Regular_22_4bpp@@YAAAVGeneratedFont@touchgfx@@XZ
	mov	eax, DWORD PTR fs:0
	push	eax
	sub	esp, 192				; 000000c0H
	push	ebx
	push	esi
	push	edi
	lea	edi, DWORD PTR [ebp-12]
	xor	ecx, ecx
	mov	eax, -858993460				; ccccccccH
	rep stosd
	mov	eax, DWORD PTR ___security_cookie
	xor	eax, ebp
	push	eax
	lea	eax, DWORD PTR __$EHRec$[ebp]
	mov	DWORD PTR fs:0, eax
	mov	ecx, OFFSET __279C6AF9_Table_Amiri_Regular_22_4bpp@cpp
	call	@__CheckForDebuggerJustMyCode@4
; Line 26
	mov	eax, DWORD PTR __tls_index
	mov	ecx, DWORD PTR fs:__tls_array
	mov	edx, DWORD PTR [ecx+eax*4]
	mov	eax, DWORD PTR ?$TSS0@?1??getFont_Amiri_Regular_22_4bpp@@YAAAVGeneratedFont@touchgfx@@XZ@4HA
	cmp	eax, DWORD PTR __Init_thread_epoch[edx]
	jle	SHORT $LN2@getFont_Am
	push	OFFSET ?$TSS0@?1??getFont_Amiri_Regular_22_4bpp@@YAAAVGeneratedFont@touchgfx@@XZ@4HA
	call	__Init_thread_header
	add	esp, 4
	cmp	DWORD PTR ?$TSS0@?1??getFont_Amiri_Regular_22_4bpp@@YAAAVGeneratedFont@touchgfx@@XZ@4HA, -1
	jne	SHORT $LN2@getFont_Am
	mov	DWORD PTR __$EHRec$[ebp+8], 0
	push	OFFSET ?Amiri_Regular_contextualFormsTable@@3UFontContextualFormsTable@touchgfx@@B ; Amiri_Regular_contextualFormsTable
	push	0
	push	0
	push	63					; 0000003fH
	push	OFFSET ?kerning_Amiri_Regular_22_4bpp@@3QBUKerningNode@touchgfx@@B ; kerning_Amiri_Regular_22_4bpp
	push	OFFSET ?unicodes_Amiri_Regular_22_4bpp@@3QBQBEB ; unicodes_Amiri_Regular_22_4bpp
	push	0
	push	0
	push	1
	push	4
	push	0
	push	22					; 00000016H
	push	1
	push	OFFSET ?glyphs_Amiri_Regular_22_4bpp@@3QBUGlyphNode@touchgfx@@B ; glyphs_Amiri_Regular_22_4bpp
	mov	ecx, OFFSET ?Amiri_Regular_22_4bpp@?1??getFont_Amiri_Regular_22_4bpp@@YAAAVGeneratedFont@touchgfx@@XZ@4V23@A
	call	??0GeneratedFont@touchgfx@@QAE@PBUGlyphNode@1@GGEEEEEPBQBEPBUKerningNode@1@GGQBGPBUFontContextualFormsTable@1@@Z ; touchgfx::GeneratedFont::GeneratedFont
	push	OFFSET ??__FAmiri_Regular_22_4bpp@?1??getFont_Amiri_Regular_22_4bpp@@YAAAVGeneratedFont@touchgfx@@XZ@YAXXZ ; `getFont_Amiri_Regular_22_4bpp'::`2'::`dynamic atexit destructor for 'Amiri_Regular_22_4bpp''
	call	_atexit
	add	esp, 4
	mov	DWORD PTR __$EHRec$[ebp+8], -1
	push	OFFSET ?$TSS0@?1??getFont_Amiri_Regular_22_4bpp@@YAAAVGeneratedFont@touchgfx@@XZ@4HA
	call	__Init_thread_footer
	add	esp, 4
$LN2@getFont_Am:
; Line 27
	mov	eax, OFFSET ?Amiri_Regular_22_4bpp@?1??getFont_Amiri_Regular_22_4bpp@@YAAAVGeneratedFont@touchgfx@@XZ@4V23@A
; Line 28
	mov	ecx, DWORD PTR __$EHRec$[ebp]
	mov	DWORD PTR fs:0, ecx
	pop	ecx
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 204				; 000000ccH
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	0
_TEXT	ENDS
;	COMDAT text$x
text$x	SEGMENT
__unwindfunclet$?getFont_Amiri_Regular_22_4bpp@@YAAAVGeneratedFont@touchgfx@@XZ$0:
	push	OFFSET ?$TSS0@?1??getFont_Amiri_Regular_22_4bpp@@YAAAVGeneratedFont@touchgfx@@XZ@4HA
	call	__Init_thread_abort
	pop	ecx
	ret	0
	int	3
	int	3
	int	3
	int	3
	int	3
__ehhandler$?getFont_Amiri_Regular_22_4bpp@@YAAAVGeneratedFont@touchgfx@@XZ:
	npad	1
	npad	1
	mov	edx, DWORD PTR [esp+8]
	lea	eax, DWORD PTR [edx+12]
	mov	ecx, DWORD PTR [edx-208]
	xor	ecx, eax
	call	@__security_check_cookie@4
	mov	eax, OFFSET __ehfuncinfo$?getFont_Amiri_Regular_22_4bpp@@YAAAVGeneratedFont@touchgfx@@XZ
	jmp	___CxxFrameHandler3
text$x	ENDS
?getFont_Amiri_Regular_22_4bpp@@YAAAVGeneratedFont@touchgfx@@XZ ENDP ; getFont_Amiri_Regular_22_4bpp
; Function compile flags: /Odtp /RTCsu /ZI
;	COMDAT ??1GeneratedFont@touchgfx@@UAE@XZ
_TEXT	SEGMENT
_this$ = -8						; size = 4
??1GeneratedFont@touchgfx@@UAE@XZ PROC			; touchgfx::GeneratedFont::~GeneratedFont, COMDAT
; _this$ = ecx
	push	ebp
	mov	ebp, esp
	sub	esp, 204				; 000000ccH
	push	ebx
	push	esi
	push	edi
	push	ecx
	lea	edi, DWORD PTR [ebp-12]
	mov	ecx, 3
	mov	eax, -858993460				; ccccccccH
	rep stosd
	pop	ecx
	mov	DWORD PTR _this$[ebp], ecx
	mov	ecx, DWORD PTR _this$[ebp]
	call	??1ConstFont@touchgfx@@UAE@XZ
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 204				; 000000ccH
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	0
??1GeneratedFont@touchgfx@@UAE@XZ ENDP			; touchgfx::GeneratedFont::~GeneratedFont
_TEXT	ENDS
; Function compile flags: /Odtp /RTCsu /ZI
;	COMDAT ??1ConstFont@touchgfx@@UAE@XZ
_TEXT	SEGMENT
_this$ = -8						; size = 4
??1ConstFont@touchgfx@@UAE@XZ PROC			; touchgfx::ConstFont::~ConstFont, COMDAT
; _this$ = ecx
	push	ebp
	mov	ebp, esp
	sub	esp, 204				; 000000ccH
	push	ebx
	push	esi
	push	edi
	push	ecx
	lea	edi, DWORD PTR [ebp-12]
	mov	ecx, 3
	mov	eax, -858993460				; ccccccccH
	rep stosd
	pop	ecx
	mov	DWORD PTR _this$[ebp], ecx
	mov	ecx, DWORD PTR _this$[ebp]
	call	??1Font@touchgfx@@UAE@XZ		; touchgfx::Font::~Font
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 204				; 000000ccH
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	0
??1ConstFont@touchgfx@@UAE@XZ ENDP			; touchgfx::ConstFont::~ConstFont
_TEXT	ENDS
; Function compile flags: /Odtp /RTCsu /ZI
;	COMDAT ??_GFont@touchgfx@@UAEPAXI@Z
_TEXT	SEGMENT
_this$ = -8						; size = 4
___flags$ = 8						; size = 4
??_GFont@touchgfx@@UAEPAXI@Z PROC			; touchgfx::Font::`scalar deleting destructor', COMDAT
; _this$ = ecx
	push	ebp
	mov	ebp, esp
	sub	esp, 204				; 000000ccH
	push	ebx
	push	esi
	push	edi
	push	ecx
	lea	edi, DWORD PTR [ebp-12]
	mov	ecx, 3
	mov	eax, -858993460				; ccccccccH
	rep stosd
	pop	ecx
	mov	DWORD PTR _this$[ebp], ecx
	mov	ecx, DWORD PTR _this$[ebp]
	call	??1Font@touchgfx@@UAE@XZ		; touchgfx::Font::~Font
	mov	eax, DWORD PTR ___flags$[ebp]
	and	eax, 1
	je	SHORT $LN2@scalar
	push	16					; 00000010H
	mov	eax, DWORD PTR _this$[ebp]
	push	eax
	call	??3@YAXPAXI@Z				; operator delete
	add	esp, 8
$LN2@scalar:
	mov	eax, DWORD PTR _this$[ebp]
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 204				; 000000ccH
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	4
??_GFont@touchgfx@@UAEPAXI@Z ENDP			; touchgfx::Font::`scalar deleting destructor'
_TEXT	ENDS
; Function compile flags: /Odtp /RTCsu /ZI
;	COMDAT ?getContextualFormsTable@Font@touchgfx@@UBEPBUFontContextualFormsTable@2@XZ
_TEXT	SEGMENT
_this$ = -8						; size = 4
?getContextualFormsTable@Font@touchgfx@@UBEPBUFontContextualFormsTable@2@XZ PROC ; touchgfx::Font::getContextualFormsTable, COMDAT
; _this$ = ecx
; File D:\学习\毕业设计\方案1_GFX+底板\官方例程\DISPLAY\Middlewares\ST\touchgfx\framework\include\touchgfx\Font.hpp
; Line 419
	push	ebp
	mov	ebp, esp
	sub	esp, 204				; 000000ccH
	push	ebx
	push	esi
	push	edi
	push	ecx
	lea	edi, DWORD PTR [ebp-12]
	mov	ecx, 3
	mov	eax, -858993460				; ccccccccH
	rep stosd
	pop	ecx
	mov	DWORD PTR _this$[ebp], ecx
	mov	ecx, OFFSET __2B5BEDA9_Font@hpp
	call	@__CheckForDebuggerJustMyCode@4
; Line 420
	xor	eax, eax
; Line 421
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 204				; 000000ccH
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	0
?getContextualFormsTable@Font@touchgfx@@UBEPBUFontContextualFormsTable@2@XZ ENDP ; touchgfx::Font::getContextualFormsTable
_TEXT	ENDS
; Function compile flags: /Odtp /RTCsu /ZI
;	COMDAT ?getGSUBTable@Font@touchgfx@@UBEPBGXZ
_TEXT	SEGMENT
_this$ = -8						; size = 4
?getGSUBTable@Font@touchgfx@@UBEPBGXZ PROC		; touchgfx::Font::getGSUBTable, COMDAT
; _this$ = ecx
; File D:\学习\毕业设计\方案1_GFX+底板\官方例程\DISPLAY\Middlewares\ST\touchgfx\framework\include\touchgfx\Font.hpp
; Line 409
	push	ebp
	mov	ebp, esp
	sub	esp, 204				; 000000ccH
	push	ebx
	push	esi
	push	edi
	push	ecx
	lea	edi, DWORD PTR [ebp-12]
	mov	ecx, 3
	mov	eax, -858993460				; ccccccccH
	rep stosd
	pop	ecx
	mov	DWORD PTR _this$[ebp], ecx
	mov	ecx, OFFSET __2B5BEDA9_Font@hpp
	call	@__CheckForDebuggerJustMyCode@4
; Line 410
	xor	eax, eax
; Line 411
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 204				; 000000ccH
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	0
?getGSUBTable@Font@touchgfx@@UBEPBGXZ ENDP		; touchgfx::Font::getGSUBTable
_TEXT	ENDS
; Function compile flags: /Odtp /RTCsu /ZI
;	COMDAT ?getKerning@Font@touchgfx@@UBECGPBUGlyphNode@2@@Z
_TEXT	SEGMENT
_this$ = -8						; size = 4
_prevChar$ = 8						; size = 2
_glyph$ = 12						; size = 4
?getKerning@Font@touchgfx@@UBECGPBUGlyphNode@2@@Z PROC	; touchgfx::Font::getKerning, COMDAT
; _this$ = ecx
; File D:\学习\毕业设计\方案1_GFX+底板\官方例程\DISPLAY\Middlewares\ST\touchgfx\framework\include\touchgfx\Font.hpp
; Line 389
	push	ebp
	mov	ebp, esp
	sub	esp, 204				; 000000ccH
	push	ebx
	push	esi
	push	edi
	push	ecx
	lea	edi, DWORD PTR [ebp-12]
	mov	ecx, 3
	mov	eax, -858993460				; ccccccccH
	rep stosd
	pop	ecx
	mov	DWORD PTR _this$[ebp], ecx
	mov	ecx, OFFSET __2B5BEDA9_Font@hpp
	call	@__CheckForDebuggerJustMyCode@4
; Line 390
	xor	al, al
; Line 391
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 204				; 000000ccH
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	8
?getKerning@Font@touchgfx@@UBECGPBUGlyphNode@2@@Z ENDP	; touchgfx::Font::getKerning
_TEXT	ENDS
; Function compile flags: /Odtp /RTCsu /ZI
;	COMDAT ?getByteAlignRow@Font@touchgfx@@UBEEXZ
_TEXT	SEGMENT
_this$ = -8						; size = 4
?getByteAlignRow@Font@touchgfx@@UBEEXZ PROC		; touchgfx::Font::getByteAlignRow, COMDAT
; _this$ = ecx
; File D:\学习\毕业设计\方案1_GFX+底板\官方例程\DISPLAY\Middlewares\ST\touchgfx\framework\include\touchgfx\Font.hpp
; Line 352
	push	ebp
	mov	ebp, esp
	sub	esp, 204				; 000000ccH
	push	ebx
	push	esi
	push	edi
	push	ecx
	lea	edi, DWORD PTR [ebp-12]
	mov	ecx, 3
	mov	eax, -858993460				; ccccccccH
	rep stosd
	pop	ecx
	mov	DWORD PTR _this$[ebp], ecx
	mov	ecx, OFFSET __2B5BEDA9_Font@hpp
	call	@__CheckForDebuggerJustMyCode@4
; Line 353
	mov	eax, DWORD PTR _this$[ebp]
	mov	al, BYTE PTR [eax+7]
	shr	al, 7
	and	al, 1
; Line 354
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 204				; 000000ccH
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	0
?getByteAlignRow@Font@touchgfx@@UBEEXZ ENDP		; touchgfx::Font::getByteAlignRow
_TEXT	ENDS
; Function compile flags: /Odtp /RTCsu /ZI
;	COMDAT ?getBitsPerPixel@Font@touchgfx@@UBEEXZ
_TEXT	SEGMENT
_this$ = -8						; size = 4
?getBitsPerPixel@Font@touchgfx@@UBEEXZ PROC		; touchgfx::Font::getBitsPerPixel, COMDAT
; _this$ = ecx
; File D:\学习\毕业设计\方案1_GFX+底板\官方例程\DISPLAY\Middlewares\ST\touchgfx\framework\include\touchgfx\Font.hpp
; Line 342
	push	ebp
	mov	ebp, esp
	sub	esp, 204				; 000000ccH
	push	ebx
	push	esi
	push	edi
	push	ecx
	lea	edi, DWORD PTR [ebp-12]
	mov	ecx, 3
	mov	eax, -858993460				; ccccccccH
	rep stosd
	pop	ecx
	mov	DWORD PTR _this$[ebp], ecx
	mov	ecx, OFFSET __2B5BEDA9_Font@hpp
	call	@__CheckForDebuggerJustMyCode@4
; Line 343
	mov	eax, DWORD PTR _this$[ebp]
	mov	al, BYTE PTR [eax+7]
	and	al, 127					; 0000007fH
; Line 344
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 204				; 000000ccH
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	0
?getBitsPerPixel@Font@touchgfx@@UBEEXZ ENDP		; touchgfx::Font::getBitsPerPixel
_TEXT	ENDS
; Function compile flags: /Odtp /RTCsu /ZI
;	COMDAT ?getMinimumTextHeight@Font@touchgfx@@UBEGXZ
_TEXT	SEGMENT
_this$ = -8						; size = 4
?getMinimumTextHeight@Font@touchgfx@@UBEGXZ PROC	; touchgfx::Font::getMinimumTextHeight, COMDAT
; _this$ = ecx
; File D:\学习\毕业设计\方案1_GFX+底板\官方例程\DISPLAY\Middlewares\ST\touchgfx\framework\include\touchgfx\Font.hpp
; Line 332
	push	ebp
	mov	ebp, esp
	sub	esp, 204				; 000000ccH
	push	ebx
	push	esi
	push	edi
	push	ecx
	lea	edi, DWORD PTR [ebp-12]
	mov	ecx, 3
	mov	eax, -858993460				; ccccccccH
	rep stosd
	pop	ecx
	mov	DWORD PTR _this$[ebp], ecx
	mov	ecx, OFFSET __2B5BEDA9_Font@hpp
	call	@__CheckForDebuggerJustMyCode@4
; Line 333
	mov	eax, DWORD PTR _this$[ebp]
	movzx	eax, WORD PTR [eax+4]
	mov	ecx, DWORD PTR _this$[ebp]
	movzx	edx, BYTE PTR [ecx+6]
	add	eax, edx
; Line 334
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 204				; 000000ccH
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	0
?getMinimumTextHeight@Font@touchgfx@@UBEGXZ ENDP	; touchgfx::Font::getMinimumTextHeight
_TEXT	ENDS
; Function compile flags: /Odtp /RTCsu /ZI
;	COMDAT ?getFontHeight@Font@touchgfx@@UBEGXZ
_TEXT	SEGMENT
_this$ = -8						; size = 4
?getFontHeight@Font@touchgfx@@UBEGXZ PROC		; touchgfx::Font::getFontHeight, COMDAT
; _this$ = ecx
; File D:\学习\毕业设计\方案1_GFX+底板\官方例程\DISPLAY\Middlewares\ST\touchgfx\framework\include\touchgfx\Font.hpp
; Line 320
	push	ebp
	mov	ebp, esp
	sub	esp, 204				; 000000ccH
	push	ebx
	push	esi
	push	edi
	push	ecx
	lea	edi, DWORD PTR [ebp-12]
	mov	ecx, 3
	mov	eax, -858993460				; ccccccccH
	rep stosd
	pop	ecx
	mov	DWORD PTR _this$[ebp], ecx
	mov	ecx, OFFSET __2B5BEDA9_Font@hpp
	call	@__CheckForDebuggerJustMyCode@4
; Line 321
	mov	eax, DWORD PTR _this$[ebp]
	mov	ax, WORD PTR [eax+4]
; Line 322
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 204				; 000000ccH
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	0
?getFontHeight@Font@touchgfx@@UBEGXZ ENDP		; touchgfx::Font::getFontHeight
_TEXT	ENDS
; Function compile flags: /Odtp /RTCsu /ZI
;	COMDAT ?getEllipsisChar@Font@touchgfx@@UBEGXZ
_TEXT	SEGMENT
_this$ = -8						; size = 4
?getEllipsisChar@Font@touchgfx@@UBEGXZ PROC		; touchgfx::Font::getEllipsisChar, COMDAT
; _this$ = ecx
; File D:\学习\毕业设计\方案1_GFX+底板\官方例程\DISPLAY\Middlewares\ST\touchgfx\framework\include\touchgfx\Font.hpp
; Line 231
	push	ebp
	mov	ebp, esp
	sub	esp, 204				; 000000ccH
	push	ebx
	push	esi
	push	edi
	push	ecx
	lea	edi, DWORD PTR [ebp-12]
	mov	ecx, 3
	mov	eax, -858993460				; ccccccccH
	rep stosd
	pop	ecx
	mov	DWORD PTR _this$[ebp], ecx
	mov	ecx, OFFSET __2B5BEDA9_Font@hpp
	call	@__CheckForDebuggerJustMyCode@4
; Line 232
	mov	eax, DWORD PTR _this$[ebp]
	mov	ax, WORD PTR [eax+12]
; Line 233
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 204				; 000000ccH
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	0
?getEllipsisChar@Font@touchgfx@@UBEGXZ ENDP		; touchgfx::Font::getEllipsisChar
_TEXT	ENDS
; Function compile flags: /Odtp /RTCsu /ZI
;	COMDAT ?getFallbackChar@Font@touchgfx@@UBEGXZ
_TEXT	SEGMENT
_this$ = -8						; size = 4
?getFallbackChar@Font@touchgfx@@UBEGXZ PROC		; touchgfx::Font::getFallbackChar, COMDAT
; _this$ = ecx
; File D:\学习\毕业设计\方案1_GFX+底板\官方例程\DISPLAY\Middlewares\ST\touchgfx\framework\include\touchgfx\Font.hpp
; Line 218
	push	ebp
	mov	ebp, esp
	sub	esp, 204				; 000000ccH
	push	ebx
	push	esi
	push	edi
	push	ecx
	lea	edi, DWORD PTR [ebp-12]
	mov	ecx, 3
	mov	eax, -858993460				; ccccccccH
	rep stosd
	pop	ecx
	mov	DWORD PTR _this$[ebp], ecx
	mov	ecx, OFFSET __2B5BEDA9_Font@hpp
	call	@__CheckForDebuggerJustMyCode@4
; Line 219
	mov	eax, DWORD PTR _this$[ebp]
	mov	ax, WORD PTR [eax+10]
; Line 220
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 204				; 000000ccH
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	0
?getFallbackChar@Font@touchgfx@@UBEGXZ ENDP		; touchgfx::Font::getFallbackChar
_TEXT	ENDS
; Function compile flags: /Odtp /RTCsu /ZI
;	COMDAT ?getGlyph@Font@touchgfx@@UBEPBUGlyphNode@2@G@Z
_TEXT	SEGMENT
_glyph$ = -44						; size = 4
_bitsPerPixelDummy$ = -29				; size = 1
_dummyPixelDataPointer$ = -20				; size = 4
_this$ = -8						; size = 4
_unicode$ = 8						; size = 2
?getGlyph@Font@touchgfx@@UBEPBUGlyphNode@2@G@Z PROC	; touchgfx::Font::getGlyph, COMDAT
; _this$ = ecx
; File D:\学习\毕业设计\方案1_GFX+底板\官方例程\DISPLAY\Middlewares\ST\touchgfx\framework\include\touchgfx\Font.hpp
; Line 199
	push	ebp
	mov	ebp, esp
	sub	esp, 240				; 000000f0H
	push	ebx
	push	esi
	push	edi
	push	ecx
	lea	edi, DWORD PTR [ebp-48]
	mov	ecx, 12					; 0000000cH
	mov	eax, -858993460				; ccccccccH
	rep stosd
	pop	ecx
	mov	DWORD PTR _this$[ebp], ecx
	mov	ecx, OFFSET __2B5BEDA9_Font@hpp
	call	@__CheckForDebuggerJustMyCode@4
; Line 200
	movzx	eax, WORD PTR _unicode$[ebp]
	test	eax, eax
	jne	SHORT $LN2@getGlyph
; Line 202
	xor	eax, eax
	jmp	SHORT $LN1@getGlyph
$LN2@getGlyph:
; Line 204
	mov	DWORD PTR _dummyPixelDataPointer$[ebp], 0
; Line 205
	mov	BYTE PTR _bitsPerPixelDummy$[ebp], 0
; Line 206
	mov	esi, esp
	lea	eax, DWORD PTR _bitsPerPixelDummy$[ebp]
	push	eax
	lea	ecx, DWORD PTR _dummyPixelDataPointer$[ebp]
	push	ecx
	movzx	edx, WORD PTR _unicode$[ebp]
	push	edx
	mov	eax, DWORD PTR _this$[ebp]
	mov	edx, DWORD PTR [eax]
	mov	ecx, DWORD PTR _this$[ebp]
	mov	eax, DWORD PTR [edx+8]
	call	eax
	cmp	esi, esp
	call	__RTC_CheckEsp
	mov	DWORD PTR _glyph$[ebp], eax
; Line 207
	mov	eax, DWORD PTR _glyph$[ebp]
$LN1@getGlyph:
; Line 208
	push	edx
	mov	ecx, ebp
	push	eax
	lea	edx, DWORD PTR $LN7@getGlyph
	call	@_RTC_CheckStackVars@8
	pop	eax
	pop	edx
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 240				; 000000f0H
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	4
	npad	3
$LN7@getGlyph:
	DD	2
	DD	$LN6@getGlyph
$LN6@getGlyph:
	DD	-20					; ffffffecH
	DD	4
	DD	$LN4@getGlyph
	DD	-29					; ffffffe3H
	DD	1
	DD	$LN5@getGlyph
$LN5@getGlyph:
	DB	98					; 00000062H
	DB	105					; 00000069H
	DB	116					; 00000074H
	DB	115					; 00000073H
	DB	80					; 00000050H
	DB	101					; 00000065H
	DB	114					; 00000072H
	DB	80					; 00000050H
	DB	105					; 00000069H
	DB	120					; 00000078H
	DB	101					; 00000065H
	DB	108					; 0000006cH
	DB	68					; 00000044H
	DB	117					; 00000075H
	DB	109					; 0000006dH
	DB	109					; 0000006dH
	DB	121					; 00000079H
	DB	0
$LN4@getGlyph:
	DB	100					; 00000064H
	DB	117					; 00000075H
	DB	109					; 0000006dH
	DB	109					; 0000006dH
	DB	121					; 00000079H
	DB	80					; 00000050H
	DB	105					; 00000069H
	DB	120					; 00000078H
	DB	101					; 00000065H
	DB	108					; 0000006cH
	DB	68					; 00000044H
	DB	97					; 00000061H
	DB	116					; 00000074H
	DB	97					; 00000061H
	DB	80					; 00000050H
	DB	111					; 0000006fH
	DB	105					; 00000069H
	DB	110					; 0000006eH
	DB	116					; 00000074H
	DB	101					; 00000065H
	DB	114					; 00000072H
	DB	0
?getGlyph@Font@touchgfx@@UBEPBUGlyphNode@2@G@Z ENDP	; touchgfx::Font::getGlyph
_TEXT	ENDS
; Function compile flags: /Odtp /RTCsu /ZI
;	COMDAT ??1Font@touchgfx@@UAE@XZ
_TEXT	SEGMENT
_this$ = -8						; size = 4
??1Font@touchgfx@@UAE@XZ PROC				; touchgfx::Font::~Font, COMDAT
; _this$ = ecx
; File D:\学习\毕业设计\方案1_GFX+底板\官方例程\DISPLAY\Middlewares\ST\touchgfx\framework\include\touchgfx\Font.hpp
; Line 168
	push	ebp
	mov	ebp, esp
	sub	esp, 204				; 000000ccH
	push	ebx
	push	esi
	push	edi
	push	ecx
	lea	edi, DWORD PTR [ebp-12]
	mov	ecx, 3
	mov	eax, -858993460				; ccccccccH
	rep stosd
	pop	ecx
	mov	DWORD PTR _this$[ebp], ecx
	mov	ecx, OFFSET __2B5BEDA9_Font@hpp
	call	@__CheckForDebuggerJustMyCode@4
	mov	eax, DWORD PTR _this$[ebp]
	mov	DWORD PTR [eax], OFFSET ??_7Font@touchgfx@@6B@
; Line 169
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 204				; 000000ccH
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	0
??1Font@touchgfx@@UAE@XZ ENDP				; touchgfx::Font::~Font
_TEXT	ENDS
END
