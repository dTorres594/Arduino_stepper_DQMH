<?xml version='1.0' encoding='UTF-8'?>
<Library LVVersion="20008000">
	<Property Name="Instrument Driver" Type="Str">True</Property>
	<Property Name="NI.Lib.Description" Type="Str">Este driver ayuda a controlar motores a pasos bipolares y unipolares utilizando un microcontrolador de la familia MSP430 de Texas Instruments.</Property>
	<Property Name="NI.Lib.Icon" Type="Bin">)!#!!!!!!!)!"1!&amp;!!!-!%!!!@````]!!!!"!!%!!!)Y!!!*Q(C=\&gt;1^5O.!%)&lt;B4VM%J.[9A0)6_AL;@)0V&amp;4IC&gt;[L16_AL_!K_1A==!&amp;`"Y;&lt;$KX%&lt;+-!YA;L&gt;+C1;L'`_(I_%J(Z=3V&gt;KFY[`(R\0\;VKTNJ\\?VUU5Y&gt;8YVPP;7&gt;'``5ZS8JT@LN80MZPTY]PNO`W``P^AM(@;;,H&lt;\YE)9OJ:)+SCHLX[YF?:)H?:)H?:)(?:!(?:!(?:!\O:-\O:-\O:-&lt;O:%&lt;O:%&lt;O:(XEVTE)B=ZOZ)MHCS54*J-E(3'IO28YEE]C3@R=+H%EXA34_**0(22YEE]C3@R*"['+@%EHM34?")05X6*^J-=4_*B?A7?Q".Y!E`A95E&amp;HA!1,":-(%Q#1U&amp;D]#(Q"*\!QU=&amp;HM!4?!*0Y+&amp;:A3@Q"*\!%XA9UH=FOG9_S@%QD2S0YX%]DM@R-,5=D_.R0)\(]&lt;#=()`D=2$/AM\E%/1-=DIY&amp;Y\(]@"(DM@R/"\(YXBI[H@)_]\-GPEERW.Y$)`B-4S'BSFE?!S0Y4%]BI&gt;J:8A-D_%R0);(J72Y$)`B-3$'ICQP9T*DI.(*#!Q00`VJM8[8IEOMH`7P?8R161_A[M&amp;304#K"U&amp;VAV5X4H6$6"ONWE$6RKC_M/K,K)#KB654KDLKQ/]^N;/WV):;5SNKJ*&lt;59B\[S2U0BY0W_\VWOZWWW[UWGYX7[\67KZ8'=&gt;2SO&gt;2CM8B[7^VS(I`B^&amp;[;_$S..].U^X/9`DQ-U[`@8.]00@`#/L[8`I6XIX[IP8D.MU?0W%&lt;&amp;_Q!!!!!</Property>
	<Property Name="NI.Lib.SourceVersion" Type="Int">536903680</Property>
	<Property Name="NI.Lib.Version" Type="Str">1.0.0.0</Property>
	<Item Name="Controls" Type="Folder">
		<Item Name="Com Port Options.ctl" Type="VI" URL="../Public/Controls/Com Port Options.ctl"/>
		<Item Name="Motor direction.ctl" Type="VI" URL="../Public/Controls/Motor direction.ctl"/>
		<Item Name="Motor info.ctl" Type="VI" URL="../Public/Controls/Motor info.ctl"/>
		<Item Name="Motor initialization parameters--cluster.ctl" Type="VI" URL="../Public/Controls/Motor initialization parameters--cluster.ctl"/>
		<Item Name="Move motor parameters--cluster.ctl" Type="VI" URL="../Public/Controls/Move motor parameters--cluster.ctl"/>
		<Item Name="Step style.ctl" Type="VI" URL="../Public/Controls/Step style.ctl"/>
	</Item>
	<Item Name="Public" Type="Folder">
		<Property Name="NI.LibItem.Scope" Type="Int">1</Property>
		<Property Name="NI.SortType" Type="Int">3</Property>
		<Item Name="Action-Status" Type="Folder">
			<Item Name="Initialize.vi" Type="VI" URL="../Public/Initialize.vi"/>
			<Item Name="Close.vi" Type="VI" URL="../Public/Close.vi"/>
			<Item Name="Stop.vi" Type="VI" URL="../Public/Stop.vi"/>
		</Item>
		<Item Name="Data" Type="Folder">
			<Item Name="Write--init.vi" Type="VI" URL="../Public/Write--init.vi"/>
			<Item Name="Read.vi" Type="VI" URL="../Public/Read.vi"/>
			<Item Name="Write--move.vi" Type="VI" URL="../Public/Write--move.vi"/>
			<Item Name="Write.vi" Type="VI" URL="../Public/Write.vi"/>
			<Item Name="Write--command.vi" Type="VI" URL="../Public/Write--command.vi"/>
			<Item Name="Write--home.vi" Type="VI" URL="../Public/Write--home.vi"/>
		</Item>
		<Item Name="Support" Type="Folder">
			<Item Name="Wait -- constant.vi" Type="VI" URL="../Public/Wait -- constant.vi"/>
			<Item Name="Check position str.vi" Type="VI" URL="../Public/Check position str.vi"/>
			<Item Name="Calculate position from parameters.vi" Type="VI" URL="../Public/Calculate position from parameters.vi"/>
			<Item Name="Check sensor str.vi" Type="VI" URL="../Public/Check sensor str.vi"/>
			<Item Name="Get position 2.vi" Type="VI" URL="../Public/Get position 2.vi"/>
			<Item Name="Set Laser PWM.vi" Type="VI" URL="../Public/Set Laser PWM.vi"/>
			<Item Name="Check endstop str.vi" Type="VI" URL="../Public/Check endstop str.vi"/>
			<Item Name="Read sensor 2.vi" Type="VI" URL="../Public/Read sensor 2.vi"/>
			<Item Name="Read endstops.vi" Type="VI" URL="../Public/Read endstops.vi"/>
			<Item Name="Get all info.vi" Type="VI" URL="../Public/Get all info.vi"/>
			<Item Name="Check info str.vi" Type="VI" URL="../Public/Check info str.vi"/>
			<Item Name="COM Port selector english.vi" Type="VI" URL="../Support/COM Port selector english.vi"/>
			<Item Name="New Path Ubication.vi" Type="VI" URL="../Support/New Path Ubication.vi"/>
			<Item Name="Save Graph Data.vi" Type="VI" URL="../Support/Save Graph Data.vi"/>
			<Item Name="Path Ubication.vi" Type="VI" URL="../Support/Path Ubication.vi"/>
			<Item Name="ABRE ARCHIVO.vi" Type="VI" URL="../Support/ABRE ARCHIVO.vi"/>
			<Item Name="Abeles Brewster Analysis.vi" Type="VI" URL="../Support/Abeles Brewster Analysis.vi"/>
			<Item Name="Filtra curva experimental.vi" Type="VI" URL="../Support/Filtra curva experimental.vi"/>
			<Item Name="calcula brewster.vi" Type="VI" URL="../Support/calcula brewster.vi"/>
			<Item Name="brewster error.vi" Type="VI" URL="../Support/brewster error.vi"/>
			<Item Name="Brewster Angle Analysis.vi" Type="VI" URL="../Support/Brewster Angle Analysis.vi"/>
			<Item Name="Create New File.vi" Type="VI" URL="../Support/Create New File.vi"/>
			<Item Name="COM Port selector español.vi" Type="VI" URL="../Support/COM Port selector español.vi"/>
			<Item Name="Accept button.ctl" Type="VI" URL="../Support/Accept button.ctl"/>
		</Item>
	</Item>
	<Item Name="Third-party" Type="Folder">
		<Property Name="NI.LibItem.Scope" Type="Int">1</Property>
		<Item Name="CH341SER" Type="Folder">
			<Item Name="DRVSETUP64" Type="Folder">
				<Item Name="DRVSETUP64.exe" Type="Document" URL="../3rd party/CH341SER/DRVSETUP64/DRVSETUP64.exe"/>
			</Item>
			<Item Name="CH341PT.DLL" Type="Document" URL="../3rd party/CH341SER/CH341PT.DLL"/>
			<Item Name="CH341S64.SYS" Type="Document" URL="../3rd party/CH341SER/CH341S64.SYS"/>
			<Item Name="CH341S98.SYS" Type="Document" URL="../3rd party/CH341SER/CH341S98.SYS"/>
			<Item Name="CH341SER.CAT" Type="Document" URL="../3rd party/CH341SER/CH341SER.CAT"/>
			<Item Name="CH341SER.INF" Type="Document" URL="../3rd party/CH341SER/CH341SER.INF"/>
			<Item Name="CH341SER.SYS" Type="Document" URL="../3rd party/CH341SER/CH341SER.SYS"/>
			<Item Name="CH341SER.VXD" Type="Document" URL="../3rd party/CH341SER/CH341SER.VXD"/>
			<Item Name="SETUP.EXE" Type="Document" URL="../3rd party/CH341SER/SETUP.EXE"/>
		</Item>
		<Item Name="Stepper_V4.ino" Type="Document" URL="../Stepper_V4/Stepper_V4.ino"/>
	</Item>
</Library>
