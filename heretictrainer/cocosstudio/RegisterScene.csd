<GameProjectFile>
  <PropertyGroup Type="Scene" Name="RegisterScene" ID="2664ed0f-0966-4be4-8412-91297b50affd" Version="2.3.1.2" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="0" Speed="1.0000" />
      <ObjectData Name="Scene" Tag="238" ctype="GameNodeObjectData">
        <Size X="1080.0000" Y="720.0000" />
        <Children>
          <AbstractNodeData Name="background" ActionTag="-1749913572" Tag="239" IconVisible="False" TopMargin="-1.2883" BottomMargin="1.2883" ctype="SpriteObjectData">
            <Size X="1080.0000" Y="720.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="540.0000" Y="361.2883" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5000" Y="0.5018" />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="Normal" Path="common_background.png" Plist="" />
            <BlendFunc Src="770" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="titlebar" ActionTag="-1522302040" Tag="240" IconVisible="False" LeftMargin="-1.4302" RightMargin="1.4302" TopMargin="-1.0000" BottomMargin="657.0000" ctype="SpriteObjectData">
            <Size X="1080.0000" Y="64.0000" />
            <Children>
              <AbstractNodeData Name="text_register" ActionTag="-284049808" Tag="242" IconVisible="False" LeftMargin="516.0000" RightMargin="516.0000" TopMargin="20.3809" BottomMargin="16.6191" FontSize="24" LabelText="注册" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                <Size X="48.0000" Y="27.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="540.0000" Y="30.1191" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="0.4706" />
                <PreSize X="0.0000" Y="0.0000" />
                <FontResource Type="Normal" Path="simhei.ttf" Plist="" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="button_return" ActionTag="-1264282844" Tag="353" IconVisible="False" LeftMargin="26.0942" RightMargin="1030.9058" TopMargin="15.8807" BottomMargin="18.1193" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="7" RightEage="7" TopEage="9" BottomEage="9" Scale9OriginX="7" Scale9OriginY="9" Scale9Width="9" Scale9Height="12" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                <Size X="23.0000" Y="30.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="37.5942" Y="33.1193" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.0348" Y="0.5175" />
                <PreSize X="0.0213" Y="0.0417" />
                <TextColor A="255" R="65" G="65" B="70" />
                <NormalFileData Type="Normal" Path="common_titlebar_returnbutton.png" Plist="" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint ScaleX="0.5000" ScaleY="1.0000" />
            <Position X="538.5698" Y="721.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.4987" Y="1.0014" />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="Normal" Path="common_titlebar_background.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="text_email" ActionTag="965552875" Tag="337" IconVisible="False" LeftMargin="180.5169" RightMargin="815.4831" TopMargin="161.7936" BottomMargin="526.2064" FontSize="28" LabelText="邮箱：" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
            <Size X="84.0000" Y="32.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="222.5169" Y="542.2064" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="77" G="77" B="77" />
            <PrePosition X="0.2060" Y="0.7531" />
            <PreSize X="0.0000" Y="0.0000" />
            <FontResource Type="Normal" Path="simhei.ttf" Plist="" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
          <AbstractNodeData Name="textfieldbackground_email" ActionTag="-1720284632" Tag="336" IconVisible="False" LeftMargin="371.5275" RightMargin="430.4725" TopMargin="157.2235" BottomMargin="518.7765" ctype="SpriteObjectData">
            <Size X="278.0000" Y="44.0000" />
            <Children>
              <AbstractNodeData Name="textfield_email" ActionTag="-1978218842" Tag="338" IconVisible="False" LeftMargin="22.1721" RightMargin="11.8279" TopMargin="12.9977" BottomMargin="2.0023" TouchEnable="True" FontSize="18" IsCustomSize="True" LabelText="" PlaceHolderText="请输入邮箱" MaxLengthText="10" ctype="TextFieldObjectData">
                <Size X="244.0000" Y="29.0000" />
                <AnchorPoint />
                <Position X="22.1721" Y="2.0023" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="77" G="77" B="77" />
                <PrePosition X="0.0798" Y="0.0455" />
                <PreSize X="0.8777" Y="0.6591" />
                <FontResource Type="Normal" Path="simhei.ttf" Plist="" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="510.5275" Y="540.7765" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.4727" Y="0.7511" />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="Normal" Path="common_textfield_background.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="text_username" ActionTag="-1803464715" Tag="340" IconVisible="False" LeftMargin="180.5168" RightMargin="787.4833" TopMargin="249.9047" BottomMargin="438.0953" FontSize="28" LabelText="用户名：" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
            <Size X="112.0000" Y="32.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="236.5168" Y="454.0953" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="77" G="77" B="77" />
            <PrePosition X="0.2190" Y="0.6307" />
            <PreSize X="0.0000" Y="0.0000" />
            <FontResource Type="Normal" Path="simhei.ttf" Plist="" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
          <AbstractNodeData Name="textfieldbackground_username" ActionTag="-1444609732" Tag="341" IconVisible="False" LeftMargin="371.5275" RightMargin="430.4725" TopMargin="245.3348" BottomMargin="430.6652" ctype="SpriteObjectData">
            <Size X="278.0000" Y="44.0000" />
            <Children>
              <AbstractNodeData Name="textField_username" ActionTag="-1303898477" Tag="342" IconVisible="False" LeftMargin="22.1721" RightMargin="11.8279" TopMargin="12.9977" BottomMargin="2.0023" TouchEnable="True" FontSize="18" IsCustomSize="True" LabelText="" PlaceHolderText="请输入用户名" MaxLengthText="10" ctype="TextFieldObjectData">
                <Size X="244.0000" Y="29.0000" />
                <AnchorPoint />
                <Position X="22.1721" Y="2.0023" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="77" G="77" B="77" />
                <PrePosition X="0.0798" Y="0.0455" />
                <PreSize X="0.8777" Y="0.6591" />
                <FontResource Type="Normal" Path="simhei.ttf" Plist="" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="510.5275" Y="452.6652" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.4727" Y="0.6287" />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="Normal" Path="common_textfield_background.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="text_password" ActionTag="-62504046" Tag="343" IconVisible="False" LeftMargin="180.5169" RightMargin="815.4831" TopMargin="338.0156" BottomMargin="349.9844" FontSize="28" LabelText="密码：" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
            <Size X="84.0000" Y="32.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="222.5169" Y="365.9844" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="77" G="77" B="77" />
            <PrePosition X="0.2060" Y="0.5083" />
            <PreSize X="0.0000" Y="0.0000" />
            <FontResource Type="Normal" Path="simhei.ttf" Plist="" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
          <AbstractNodeData Name="textfieldbackground_password" ActionTag="753926140" Tag="344" IconVisible="False" LeftMargin="371.5275" RightMargin="430.4725" TopMargin="333.4458" BottomMargin="342.5542" ctype="SpriteObjectData">
            <Size X="278.0000" Y="44.0000" />
            <Children>
              <AbstractNodeData Name="textField_password" ActionTag="2089189391" Tag="345" IconVisible="False" LeftMargin="22.1721" RightMargin="11.8279" TopMargin="12.9977" BottomMargin="2.0023" TouchEnable="True" FontSize="18" IsCustomSize="True" LabelText="" PlaceHolderText="请输入密码" MaxLengthText="10" ctype="TextFieldObjectData">
                <Size X="244.0000" Y="29.0000" />
                <AnchorPoint />
                <Position X="22.1721" Y="2.0023" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="77" G="77" B="77" />
                <PrePosition X="0.0798" Y="0.0455" />
                <PreSize X="0.8777" Y="0.6591" />
                <FontResource Type="Normal" Path="simhei.ttf" Plist="" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="510.5275" Y="364.5542" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.4727" Y="0.5063" />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="Normal" Path="common_textfield_background.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="text_repty" ActionTag="-1926168160" Tag="346" IconVisible="False" LeftMargin="180.5172" RightMargin="759.4828" TopMargin="426.1261" BottomMargin="261.8739" FontSize="28" LabelText="重复密码：" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
            <Size X="140.0000" Y="32.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="250.5172" Y="277.8739" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="77" G="77" B="77" />
            <PrePosition X="0.2320" Y="0.3859" />
            <PreSize X="0.0000" Y="0.0000" />
            <FontResource Type="Normal" Path="simhei.ttf" Plist="" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
          <AbstractNodeData Name="textfieldbackground_repty" ActionTag="-1888479432" Tag="347" IconVisible="False" LeftMargin="371.5275" RightMargin="430.4725" TopMargin="421.5560" BottomMargin="254.4440" ctype="SpriteObjectData">
            <Size X="278.0000" Y="44.0000" />
            <Children>
              <AbstractNodeData Name="textField_repty" ActionTag="-111881472" Tag="348" IconVisible="False" LeftMargin="22.1721" RightMargin="11.8279" TopMargin="12.9977" BottomMargin="2.0023" TouchEnable="True" FontSize="18" IsCustomSize="True" LabelText="" PlaceHolderText="请重复一遍所输入的密码" MaxLengthText="10" ctype="TextFieldObjectData">
                <Size X="244.0000" Y="29.0000" />
                <AnchorPoint />
                <Position X="22.1721" Y="2.0023" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="77" G="77" B="77" />
                <PrePosition X="0.0798" Y="0.0455" />
                <PreSize X="0.8777" Y="0.6591" />
                <FontResource Type="Normal" Path="simhei.ttf" Plist="" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="510.5275" Y="276.4440" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.4727" Y="0.3839" />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="Normal" Path="common_textfield_background.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="text_code" ActionTag="-1685360118" Tag="349" IconVisible="False" LeftMargin="180.5168" RightMargin="787.4833" TopMargin="514.2366" BottomMargin="173.7634" FontSize="28" LabelText="邀请码：" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
            <Size X="112.0000" Y="32.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="236.5168" Y="189.7634" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="77" G="77" B="77" />
            <PrePosition X="0.2190" Y="0.2636" />
            <PreSize X="0.0000" Y="0.0000" />
            <FontResource Type="Normal" Path="simhei.ttf" Plist="" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
          <AbstractNodeData Name="textfieldbackground_code" ActionTag="-607529914" Tag="350" IconVisible="False" LeftMargin="371.5275" RightMargin="430.4725" TopMargin="509.6662" BottomMargin="166.3338" ctype="SpriteObjectData">
            <Size X="278.0000" Y="44.0000" />
            <Children>
              <AbstractNodeData Name="textField_code" ActionTag="1301013396" Tag="351" IconVisible="False" LeftMargin="22.1721" RightMargin="11.8279" TopMargin="12.9977" BottomMargin="2.0023" TouchEnable="True" FontSize="18" IsCustomSize="True" LabelText="" PlaceHolderText="请输入邀请码（可为空）" MaxLengthText="10" ctype="TextFieldObjectData">
                <Size X="244.0000" Y="29.0000" />
                <AnchorPoint />
                <Position X="22.1721" Y="2.0023" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="77" G="77" B="77" />
                <PrePosition X="0.0798" Y="0.0455" />
                <PreSize X="0.8777" Y="0.6591" />
                <FontResource Type="Normal" Path="simhei.ttf" Plist="" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="510.5275" Y="188.3338" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.4727" Y="0.2616" />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="Normal" Path="common_textfield_background.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="button_register" ActionTag="1452404519" Tag="352" IconVisible="False" LeftMargin="362.5886" RightMargin="569.4114" TopMargin="608.3844" BottomMargin="58.6156" TouchEnable="True" FontSize="25" ButtonText="注册" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="118" Scale9Height="31" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
            <Size X="148.0000" Y="53.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="436.5886" Y="85.1156" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.4042" Y="0.1182" />
            <PreSize X="0.1370" Y="0.0736" />
            <FontResource Type="Normal" Path="simhei.ttf" Plist="" />
            <TextColor A="255" R="230" G="230" B="250" />
            <DisabledFileData Type="Normal" Path="common_button2_normal.png" Plist="" />
            <PressedFileData Type="Normal" Path="common_button2_pressed.png" Plist="" />
            <NormalFileData Type="Normal" Path="common_button2_normal.png" Plist="" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
          <AbstractNodeData Name="text_email_empty" ActionTag="-271807935" Tag="421" IconVisible="False" LeftMargin="-167.0361" RightMargin="1139.0361" TopMargin="609.3168" BottomMargin="89.6832" FontSize="18" LabelText="邮箱不能为空" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
            <Size X="108.0000" Y="21.0000" />
            <AnchorPoint ScaleX="0.4726" ScaleY="0.3700" />
            <Position X="-115.9910" Y="97.4537" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="-0.1074" Y="0.1354" />
            <PreSize X="0.0000" Y="0.0000" />
            <FontResource Type="Normal" Path="simhei.ttf" Plist="" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
          <AbstractNodeData Name="text_username_empty" ActionTag="-641605425" Tag="422" IconVisible="False" LeftMargin="-165.4654" RightMargin="1137.4653" TopMargin="649.5604" BottomMargin="49.4396" FontSize="18" LabelText="用户名不能为空" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
            <Size X="126.0000" Y="21.0000" />
            <AnchorPoint ScaleX="0.4726" ScaleY="0.3700" />
            <Position X="-114.4202" Y="57.2101" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="-0.1059" Y="0.0795" />
            <PreSize X="0.0000" Y="0.0000" />
            <FontResource Type="Normal" Path="simhei.ttf" Plist="" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
          <AbstractNodeData Name="text_password_empty" ActionTag="-678361774" Tag="423" IconVisible="False" LeftMargin="-169.7562" RightMargin="1141.7562" TopMargin="688.1772" BottomMargin="10.8228" FontSize="18" LabelText="密码不能为空" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
            <Size X="108.0000" Y="21.0000" />
            <AnchorPoint ScaleX="0.4726" ScaleY="0.3700" />
            <Position X="-118.7110" Y="18.5933" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="-0.1099" Y="0.0258" />
            <PreSize X="0.0000" Y="0.0000" />
            <FontResource Type="Normal" Path="simhei.ttf" Plist="" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
          <AbstractNodeData Name="text_repty_empty" ActionTag="1762447405" Tag="424" IconVisible="False" LeftMargin="-152.6671" RightMargin="1142.6671" TopMargin="726.7941" BottomMargin="-27.7941" FontSize="18" LabelText="请重复密码" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
            <Size X="90.0000" Y="21.0000" />
            <AnchorPoint ScaleX="0.4726" ScaleY="0.3700" />
            <Position X="-110.1295" Y="-20.0236" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="-0.1020" Y="-0.0278" />
            <PreSize X="0.0000" Y="0.0000" />
            <FontResource Type="Normal" Path="simhei.ttf" Plist="" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
          <AbstractNodeData Name="text_password_wrong" ActionTag="-1884981160" Tag="425" IconVisible="False" LeftMargin="-152.6669" RightMargin="1142.6669" TopMargin="756.8293" BottomMargin="-57.8293" FontSize="18" LabelText="两次输入密码不相同" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
            <Size X="162.0000" Y="21.0000" />
            <AnchorPoint ScaleX="0.4726" ScaleY="0.3700" />
            <Position X="-110.1293" Y="-50.0588" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="-0.1020" Y="-0.0695" />
            <PreSize X="0.0000" Y="0.0000" />
            <FontResource Type="Normal" Path="simhei.ttf" Plist="" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
          <AbstractNodeData Name="text_register_fail" ActionTag="440186426" Tag="426" IconVisible="False" LeftMargin="-168.4368" RightMargin="1167.4368" TopMargin="490.8024" BottomMargin="208.1976" FontSize="18" LabelText="注册失败!" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
            <Size X="81.0000" Y="21.0000" />
            <AnchorPoint ScaleX="0.4903" ScaleY="0.8468" />
            <Position X="-128.7227" Y="225.9799" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="-0.1192" Y="0.3139" />
            <PreSize X="0.0000" Y="0.0000" />
            <FontResource Type="Normal" Path="simhei.ttf" Plist="" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
          <AbstractNodeData Name="text_register_successed" ActionTag="954108121" Tag="427" IconVisible="False" LeftMargin="-165.5763" RightMargin="1164.5763" TopMargin="525.1284" BottomMargin="173.8716" FontSize="18" LabelText="注册成功!" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
            <Size X="81.0000" Y="21.0000" />
            <AnchorPoint ScaleX="0.4903" ScaleY="0.8468" />
            <Position X="-125.8622" Y="191.6538" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="-0.1165" Y="0.2662" />
            <PreSize X="0.0000" Y="0.0000" />
            <FontResource Type="Normal" Path="simhei.ttf" Plist="" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameProjectFile>