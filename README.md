# YUVEdit
This program modifies images of the video sequence in a YUV file. Every image of each frame is first divided into four equal parts. Then, the opposite parts of the image of a given frame are changed with each other, at specified time intervals. The exact process is shown in the image below. This program was created to test the efficiency of video codecs under a frequent scene change conditions. Currently, there are supported only yuv files with 4:2:0 chroma subsampling.

<p align="center">
<img align="center" src="https://dl.dropboxusercontent.com/s/m1b7sns1kd10bdo/1234%20-%204231%20400%2010.png" width="608" height="144">
</p>

## Usage

Program must be started with the following arguments in the same order:
- `[Input patch]` - Patch to intput yuv file
- `[Output patch]` - Patch to output yuv file
- `[Number of frames to process]` - Number of frames that program will process from input file to output file
- `[Frequncy of change]` - Number of frames at which an image change will occur in the sequence
- `[X resolution]` - Width of video sequence
- `[Y resolution]` - Height of video sequence
- `[Start of change (0/1)]` - **0** – if change of frame should start from first frame or **1** – if change of frame should start after number of frames specified in frequncy of change


Example use:
```bash
YUVEdit.exe input.yuv output.yuv 500 4 1920 1080 0
```

<p align="center">
<img align="center" src="https://dl.dropboxusercontent.com/s/gxuukqmccbcnw6i/240.gif" width="427" height="240">
</p>
