################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../ChatRoom.cpp \
../Console.cpp \
../Engine.cpp \
../MTCPListener.cpp \
../MessageHeaders.cpp \
../Parser.cpp \
../ServerCommunicator.cpp \
../TCPSocket.cpp \
../UDPListener.cpp \
../UDPSocket.cpp \
../UserChat.cpp \
../main.cpp 

OBJS += \
./ChatRoom.o \
./Console.o \
./Engine.o \
./MTCPListener.o \
./MessageHeaders.o \
./Parser.o \
./ServerCommunicator.o \
./TCPSocket.o \
./UDPListener.o \
./UDPSocket.o \
./UserChat.o \
./main.o 

CPP_DEPS += \
./ChatRoom.d \
./Console.d \
./Engine.d \
./MTCPListener.d \
./MessageHeaders.d \
./Parser.d \
./ServerCommunicator.d \
./TCPSocket.d \
./UDPListener.d \
./UDPSocket.d \
./UserChat.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


