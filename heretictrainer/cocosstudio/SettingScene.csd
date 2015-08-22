<GameProjectFile>
  <PropertyGroup Type="Scene" Name="SettingScene" ID="0532a0c6-b619-47a0-aa55-bdbfbe998a43" Version="2.3.1.2" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="0" Speed="1.0000" />
      <ObjectData Name="Scene" Tag="108" ctype="GameNodeObjectData">
        <Size X="1080.0000" Y="720.0000" />
        <Children>
          <AbstractNodeData Name="background" ActionTag="402030850" Tag="109" IconVisible="False" ctype="SpriteObjectData">
            <Size X="1080.0000" Y="720.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="540.0000" Y="360.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5000" Y="0.5000" />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="Normal" Path="common_background.png" Plist="" />
            <BlendFunc Src="770" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="titlbar_backgroun" ActionTag="729109701" Tag="110" IconVisible="False" BottomMargin="656.0000" ctype="SpriteObjectData">
            <Size X="1080.0000" Y="64.0000" />
            <AnchorPoint ScaleY="1.0000" />
            <Position Y="720.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition Y="1.0000" />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="Normal" Path="common_titlebar_background.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="checkbox1" ActionTag="216185781" Tag="206" IconVisible="False" LeftMargin="91.1131" RightMargin="956.8869" TopMargin="216.9605" BottomMargin="471.0395" TouchEnable="True" ctype="CheckBoxObjectData">
            <Size X="32.0000" Y="32.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="107.1131" Y="487.0395" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.0992" Y="0.6764" />
            <PreSize X="0.0296" Y="0.0444" />
            <NormalBackFileData Type="Normal" Path="common_checkbox_background.png" Plist="" />
            <PressedBackFileData Type="Normal" Path="common_checkbox_background.png" Plist="" />
            <DisableBackFileData Type="Normal" Path="common_checkbox_background.png" Plist="" />
            <NodeNormalFileData Type="Normal" Path="common_checkbox_flag.png" Plist="" />
            <NodeDisableFileData Type="Normal" Path="common_checkbox_flag.png" Plist="" />
          </AbstractNodeData>
          <AbstractNodeData Name="slider_delaysetting" ActionTag="-935004839" Tag="208" IconVisible="False" LeftMargin="240.6093" RightMargin="157.3907" TopMargin="133.0751" BottomMargin="573.9249" TouchEnable="True" PercentInfo="50" ctype="SliderObjectData">
            <Size X="682.0000" Y="13.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="581.6093" Y="580.4249" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5385" Y="0.8061" />
            <PreSize X="0.6315" Y="0.0181" />
            <BackGroundData Type="Normal" Path="common_slidebar_background.png" Plist="" />
            <ProgressBarData Type="Normal" Path="common_slidebar_front.png" Plist="" />
            <BallNormalData Type="Normal" Path="common_slidebar_button.png" Plist="" />
            <BallPressedData Type="Normal" Path="common_slidebar_button.png" Plist="" />
            <BallDisabledData Type="Normal" Path="common_slidebar_button.png" Plist="" />
          </AbstractNodeData>
          <AbstractNodeData Name="text_delaysetting" ActionTag="-660785829" Tag="290" IconVisible="False" LeftMargin="86.0411" RightMargin="876.9589" TopMargin="126.8412" BottomMargin="563.1588" FontSize="26" LabelText="节奏设置:" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
            <Size X="117.0000" Y="30.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="144.5411" Y="578.1588" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="77" G="77" B="77" />
            <PrePosition X="0.1338" Y="0.8030" />
            <PreSize X="0.0000" Y="0.0000" />
            <FontResource Type="Normal" Path="simhei.ttf" Plist="" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
          <AbstractNodeData Name="text_delaysetting_time" ActionTag="-2081514862" Tag="291" IconVisible="False" LeftMargin="961.5140" RightMargin="91.4860" TopMargin="127.8901" BottomMargin="571.1099" FontSize="18" LabelText="0ms" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
            <Size X="27.0000" Y="21.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="975.0140" Y="581.6099" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="127" G="127" B="127" />
            <PrePosition X="0.9028" Y="0.8078" />
            <PreSize X="0.0000" Y="0.0000" />
            <FontResource Type="Normal" Path="simhei.ttf" Plist="" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
          <AbstractNodeData Name="text1" ActionTag="-664138455" Tag="293" IconVisible="False" LeftMargin="141.3765" RightMargin="717.6235" TopMargin="221.2375" BottomMargin="468.7625" FontSize="26" LabelText="允许3G/4G下载歌曲" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
            <Size X="221.0000" Y="30.0000" />
            <AnchorPoint ScaleY="0.5000" />
            <Position X="141.3765" Y="483.7625" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="77" G="77" B="77" />
            <PrePosition X="0.1309" Y="0.6719" />
            <PreSize X="0.0000" Y="0.0000" />
            <FontResource Type="Normal" Path="simhei.ttf" Plist="" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
          <AbstractNodeData Name="checkbox2" ActionTag="-974585725" Tag="295" IconVisible="False" LeftMargin="91.1131" RightMargin="956.8869" TopMargin="286.4346" BottomMargin="401.5654" TouchEnable="True" ctype="CheckBoxObjectData">
            <Size X="32.0000" Y="32.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="107.1131" Y="417.5654" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.0992" Y="0.5800" />
            <PreSize X="0.0296" Y="0.0444" />
            <NormalBackFileData Type="Normal" Path="common_checkbox_background.png" Plist="" />
            <PressedBackFileData Type="Normal" Path="common_checkbox_background.png" Plist="" />
            <DisableBackFileData Type="Normal" Path="common_checkbox_background.png" Plist="" />
            <NodeNormalFileData Type="Normal" Path="common_checkbox_flag.png" Plist="" />
            <NodeDisableFileData Type="Normal" Path="common_checkbox_flag.png" Plist="" />
          </AbstractNodeData>
          <AbstractNodeData Name="text2" ActionTag="1709714134" Tag="296" IconVisible="False" LeftMargin="141.3765" RightMargin="652.6235" TopMargin="290.7126" BottomMargin="399.2874" FontSize="26" LabelText="随机模式使用旧随机算法" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
            <Size X="286.0000" Y="30.0000" />
            <AnchorPoint ScaleY="0.5000" />
            <Position X="141.3765" Y="414.2874" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="77" G="77" B="77" />
            <PrePosition X="0.1309" Y="0.5754" />
            <PreSize X="0.0000" Y="0.0000" />
            <FontResource Type="Normal" Path="simhei.ttf" Plist="" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
          <AbstractNodeData Name="checkbox3" ActionTag="634655701" Tag="297" IconVisible="False" LeftMargin="91.1131" RightMargin="956.8869" TopMargin="347.9059" BottomMargin="340.0941" TouchEnable="True" ctype="CheckBoxObjectData">
            <Size X="32.0000" Y="32.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="107.1131" Y="356.0941" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.0992" Y="0.4946" />
            <PreSize X="0.0296" Y="0.0444" />
            <NormalBackFileData Type="Normal" Path="common_checkbox_background.png" Plist="" />
            <PressedBackFileData Type="Normal" Path="common_checkbox_background.png" Plist="" />
            <DisableBackFileData Type="Normal" Path="common_checkbox_background.png" Plist="" />
            <NodeNormalFileData Type="Normal" Path="common_checkbox_flag.png" Plist="" />
            <NodeDisableFileData Type="Normal" Path="common_checkbox_flag.png" Plist="" />
          </AbstractNodeData>
          <AbstractNodeData Name="text3" ActionTag="1360607988" Tag="298" IconVisible="False" LeftMargin="141.3765" RightMargin="756.6235" TopMargin="352.1844" BottomMargin="337.8156" FontSize="26" LabelText="加载自定义主题" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
            <Size X="182.0000" Y="30.0000" />
            <AnchorPoint ScaleY="0.5000" />
            <Position X="141.3765" Y="352.8156" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="77" G="77" B="77" />
            <PrePosition X="0.1309" Y="0.4900" />
            <PreSize X="0.0000" Y="0.0000" />
            <FontResource Type="Normal" Path="simhei.ttf" Plist="" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
          <AbstractNodeData Name="button_return" ActionTag="987644863" Tag="300" IconVisible="False" LeftMargin="33.8064" RightMargin="1023.1936" TopMargin="15.8148" BottomMargin="674.1852" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="7" RightEage="7" TopEage="9" BottomEage="9" Scale9OriginX="7" Scale9OriginY="9" Scale9Width="9" Scale9Height="12" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
            <Size X="23.0000" Y="30.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="45.3064" Y="689.1852" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.0420" Y="0.9572" />
            <PreSize X="0.0213" Y="0.0417" />
            <TextColor A="255" R="65" G="65" B="70" />
            <NormalFileData Type="Normal" Path="common_titlebar_returnbutton.png" Plist="" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
          <AbstractNodeData Name="titlebar_title" ActionTag="-2078382505" Tag="301" IconVisible="False" LeftMargin="516.0000" RightMargin="516.0000" TopMargin="21.5000" BottomMargin="671.5000" FontSize="24" LabelText="设置" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
            <Size X="48.0000" Y="27.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="540.0000" Y="685.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5000" Y="0.9514" />
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