<h1 align="center">
  <br>
  The Encrypted Reaper
  <br>
</h1>

<h4 align="center">
This is a program that takes a binary file and encrypts the shellcode inside using the encryption method that you desire and spits out the files to better help assist in your loader development. The program will give you the files needed to hide your encrypted shellcode inside of the resource section of the PE. It also gives you the encryption keys for decrypting at runtime when needed as well as the iv for the AES option.
</h4>

<p align="center">
  <a href="#key-features">Key Features</a> •
  <a href="#how-to-use">How To Use</a> •
  <a href="#download">Download</a> •
  <a href="#reach-me-here">Reach Me Here</a> •
  <a href="#support">Support</a>
</p>

![Desktop-screenshot (5)](https://user-images.githubusercontent.com/111126641/198910778-7bc03be6-3742-4707-ab80-d4e6b483812f.png)



## Key Features

* AES Encryption
* RC4 Encryption
* XOR Encryption
* Hide encrypted binary or shellcode in resource section for your loader

## How To Use

To run this application, you'll need the powerreverse.ps1 file executed on target pc.

```bash
# Install This Repository
$ Download The Code By Pressing Download ZIP

# Navigate To The Build Folder Where The Exe Is Located & Pass The Arguments
$ EncryptedReaper.exe <.bin File> <Encryption Algorithm>

# The Files Spit Out Should Be In The Directory & Copy Paste Your Keys & IV Into File Where It Is Needed
$ Last Thing To Do Is To Enjoy
```

## Download

You can download the code from the top right, it will give you all the code needed in a ZIP file.

## Reach Me Here

If you want to discuss any topics or need some help I am very active and can get back to you within 24 hours or less 
And Setup A Date & Time To Help With Whatever It Is You Need, I Am Also Open To Collab On Projects I Feel Are Worth My Time
And Of My Interest As Well!!
* Twitter [@ItsCyberAli](https://twitter.com/ItsCyberAli)
* GitHub [@ItsCyberAli](https://github.com/ItsCyberAli)

## Support

<p>To Support Me You Can Buy Me A Coffee</p> 

<a href="https://www.buymeacoffee.com/ItsCyberAli" target="_blank"><img src="https://www.buymeacoffee.com/assets/img/custom_images/purple_img.png" alt="Buy Me A Coffee" style="height: 41px !important;width: 174px !important;box-shadow: 0px 3px 2px 0px rgba(190, 190, 190, 0.5) !important;-webkit-box-shadow: 0px 3px 2px 0px rgba(190, 190, 190, 0.5) !important;" ></a>

<p>Or Just Follow Me On Twitter As Well</p> 

<a href="https://twitter.com/ItsCyberAli">
	<img src="https://imgs.search.brave.com/f4D618R1h5bFKTM3AxujnMLyA5IZhP8iWVpc2VnHU68/rs:fit:1200:628:1/g:ce/aHR0cHM6Ly93d3cu/MTJjYXJhY3Rlcmlz/dGljYXMuY29tL3dw/LWNvbnRlbnQvdXBs/b2Fkcy8yMDE3LzEy/L2NhcmFjdGVyJUMz/JUFEc3RpY2FzLWRl/LXR3aXR0ZXIuanBn" width="160">
</a>

## Credit
--I did use the Library for AES from the following: https://github.com/kokke/tiny-AES-c

--I also want to give a shoutout to https://github.com/ORCx41 for help!
