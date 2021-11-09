clc
close all 
clear all

%% Transmitter Side
%% generate the random sequence of bits

totalbits=256;
SourceBit= round(rand(1,totalbits));
SourceBit=reshape(SourceBit,length(SourceBit)/4,4);

%% FEC Encoder (Hamming Coding)
n=7;
k=4; % since our message is 4 bits
linearcode=encode(SourceBit,n,k,'hamming');

%% Block Interleaverb
bi_linear=matintrlv(linearcode,8,8);

%% Modulation 
% 1) 8-QAM Modulation
modbits=bi_linear.';
for i=1:length(modbits)
    mod_linear_8qam(:,i)=qammod(bi_linear(i,:), 8);
end

% 2) 16-QAM Modulation
for i=1:length(modbits)
    mod_linear_16qam(:,i)=qammod(bi_linear(i,:), 16);
end

%% Channel model
% 1) AWGN channel
channel8QAM = comm.AWGNChannel('EbNo',15,'BitsPerSymbol',1); % 	efine a channel model
channel16QAM = comm.AWGNChannel('EbNo',15,'BitsPerSymbol',2);
awgn_8qam=channel8QAM(mod_linear_8qam);
awgn_16qam = channel16QAM(mod_linear_16qam);


%% Receiver Side
%% Demodulation
for i=1:length(awgn_8qam)
    awgnD8_linear(:,i) = qamdemod(awgn_8qam(:,i),8);
    awgnD16_linear(:,i) = qamdemod(awgn_16qam(:,i),16);
   
end
%% FEC Decoder
%Linear Decoder
for i=1:length(awgnD8_linear)
    awgn_linear_8qam(:,i) = decode(awgnD8_linear(:,i),n,k);
    awgn_linear_16qam(:,i) = decode(awgnD16_linear(:,i),n,k);
    
end
%% Deinterleaver
% first take the transpose 
awgn_linear_8qam=awgn_linear_8qam';
awgn_linear_16qam=awgn_linear_16qam';
% Block Deinterleaving
awgnlinear_8qam = matdeintrlv(awgn_linear_8qam, 8, 8);
awgnlinear_4 = matdeintrlv(awgn_linear_16qam, 8, 8);

%% BER Calculation
% Linear AWGN
% BER Plots
EbNo = 1:1:12;
M1=8; % symbols in 8qam
M2=16; % symbols in 16qam
den=1;
num1 = ones(8,1)/8; % for 8qam
num2 = ones(16,1)/16; % for 16qam
Nsamp=100; % number of samples to be considered
TX_8qam=mod_linear_8qam(:);
TX_16qam=mod_linear_16qam(:);
RX_8qam_awgn=awgn_8qam(:);
RX_16qam_awgn=awgn_16qam(:);
ber_linear_AWGN_2 = semianalytic(TX_8qam,RX_8qam_awgn,'psk/nondiff',M1,Nsamp,num1,den,EbNo);
ber_linear_AWGN_4 = semianalytic(TX_16qam,RX_16qam_awgn,'psk/nondiff',M2,Nsamp,num2,den,EbNo);
figure(1)
semilogy(EbNo,ber_linear_AWGN_2);
hold on
semilogy(EbNo,ber_linear_AWGN_4);
grid on
xlabel('EbNo');
ylabel('BER');
legend('AWGN 16QAM','AWGN 8QAM')