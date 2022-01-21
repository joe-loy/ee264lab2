fs = 32000

fc = 1000

A = 0.5; % Amplitude

totalTime = 2 % seconds

fadeTime = .25;

t = 0 : 1 / fs : totalTime;

fadeSamples = .25 * fs;

fadeWindow = linspace(0, 1, fadeSamples);

y = A * sin(2 * pi * fc * t);

y(1:length(fadeWindow)) = y(1:length(fadeWindow)) .* fadeWindow;

y(end - length(fadeWindow) + 1:end) = y(end - length(fadeWindow) + 1:end) .* fliplr(fadeWindow);

sound(y, fs)

fileName = "tone_" + num2str(fc) + "_" + num2str(fs)

audiowrite(char(fileName + ".wav"), y, fs)

if ismac
    cmd = "afconvert -f caff -d LEI16@" + num2str(fs) + " -c 1 " + fileName + ".wav " + fileName + ".caf"
end

system(cmd)