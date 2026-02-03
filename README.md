# EmbeddedCourse
Embedded programing with Proteus course from university

# Results

## Lab 1

The button is not pressed:<br>
<img width="945" height="567" alt="image" src="https://github.com/user-attachments/assets/ede77c36-b0bc-449a-bfad-c527197ad8c9" />

The button is pressed:<br>
<img width="945" height="580" alt="image" src="https://github.com/user-attachments/assets/2991e0c8-8940-4441-8f05-56cc287b398b" />

When button is either pressed or not, but timer disabled the LEDs for a moment (it alternates between enabled and disabled):<br>
<img width="945" height="550" alt="image" src="https://github.com/user-attachments/assets/cb0c6d99-cd9c-4806-9df4-18b67de1f54b" />

PWM configuration result shown with Oscilloscope:<br>
<img width="945" height="625" alt="image" src="https://github.com/user-attachments/assets/48e72073-65ff-4683-89dd-3be6ee30306d" />

## Lab 2

Scheme:<br>
<img width="945" height="1000" alt="image" src="https://github.com/user-attachments/assets/a618a86b-c936-4f8b-a56d-bb9920e6600c" />

ADC values change when moving it, outputted by USART:<br>
<img width="498" height="275" alt="image" src="https://github.com/user-attachments/assets/e9731de7-43f4-4692-a404-05cbb3657ec9" />

Using USART as a console for executing commands:<br>
<img width="673" height="344" alt="image" src="https://github.com/user-attachments/assets/b05744df-1cb0-40fa-afee-95785a28b3e8" />

Changing the PWM delay in real-time using USART console:<br>
<img width="880" height="309" alt="image" src="https://github.com/user-attachments/assets/848fa203-6054-41b3-bce0-acf7a9323913" />

# Code

## Lab 1

Main function:<br>
<img width="685" height="603" alt="image" src="https://github.com/user-attachments/assets/df89d618-26b9-4021-b581-5f0f23ca56e1" />

Dynamic address getters:<br>
<img width="630" height="343" alt="image" src="https://github.com/user-attachments/assets/0aeb9236-9a03-4063-b475-4c92f55584f6" />
<img width="349" height="288" alt="image" src="https://github.com/user-attachments/assets/c890ec8f-e563-4be0-a76e-81e914e6d67a" />

Util functions:<br>
<img width="785" height="516" alt="image" src="https://github.com/user-attachments/assets/bd2c5848-ba69-4367-97bf-0f34b1779d77" />

Function that updates lights depending on timer and button press:<br>
<img width="764" height="395" alt="image" src="https://github.com/user-attachments/assets/3109bce7-eacc-4585-b8f0-69761430f39c" />

Button and timer callbacks:<br>
<img width="385" height="196" alt="image" src="https://github.com/user-attachments/assets/a7f47080-28b6-4af4-9989-e8e792bff0c6" />
<img width="411" height="168" alt="image" src="https://github.com/user-attachments/assets/b1585b84-89a2-4770-9f45-cfdb7ad92ce3" />

Configuration of button and timer:<br>
<img width="452" height="249" alt="image" src="https://github.com/user-attachments/assets/4c5b3139-bacf-491e-92b5-d54d2866987f" />
<img width="515" height="195" alt="image" src="https://github.com/user-attachments/assets/30d34195-841a-4830-9a9a-7c121dd936e0" />

Get PSC function that calculates PSC based on board parameters:<br>
<img width="504" height="462" alt="image" src="https://github.com/user-attachments/assets/24e26e48-2335-4e91-8a41-8d4aab93d013" />

PWM configuration:<br>
<img width="945" height="264" alt="image" src="https://github.com/user-attachments/assets/6f034654-4ac5-4b92-b746-7e196e63a4f1" />

## Lab 2

Main function:<br>
<img width="945" height="600" alt="image" src="https://github.com/user-attachments/assets/f5319c2e-7423-4cb7-b251-6bb4475533f9" />

ADC configuration:<br>
<img width="945" height="461" alt="image" src="https://github.com/user-attachments/assets/e5fe2b2d-14c7-474c-986d-de2b14c4b23a" />

USART configuration:<br>
<img width="834" height="395" alt="image" src="https://github.com/user-attachments/assets/f6185caa-f2fd-4491-b26e-c8f41ce8f56e" />

USART helper functions:<br>
<img width="469" height="478" alt="image" src="https://github.com/user-attachments/assets/f84ebf1b-c548-457c-8ccd-7bc58a781864" />

Console interrupt handling:<br>
<img width="511" height="514" alt="image" src="https://github.com/user-attachments/assets/dbd5b977-c8ac-4819-abe6-57cdffdc4494" />

Command parsing:<br>
<img width="745" height="732" alt="image" src="https://github.com/user-attachments/assets/af8de258-b8b0-45b5-a4c6-2d113e5050f4" />
<img width="670" height="298" alt="image" src="https://github.com/user-attachments/assets/d7d715c5-d0e6-4708-ae0a-2b477727a65e" />

Console helper functions:<br>
<img width="533" height="238" alt="image" src="https://github.com/user-attachments/assets/a531d0c2-9dcf-4e31-936d-89e71b9bf442" />
<img width="443" height="263" alt="image" src="https://github.com/user-attachments/assets/348a07d7-fbff-4da7-9df3-09bb1ed43ce0" />


