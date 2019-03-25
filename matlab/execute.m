
rpi = raspi();
cam = cameraboard(rpi, 'Resolution', '160x120');
% cam.Rotation = 270;
% cam.VerticalFlip = true;


figure(1);
roi = [0.00 0.56 1.00 0.20];
cam.ROI = [0 0 1 1];
for i = 1:10
    img1 = snapshot(cam);
end
subplot(2,2,[1 3]);
image(img1);
drawnow;
rect = rectangle('Position',roi.*[160 120 160 120], 'EdgeColor','green', 'LineWidth',3);
for i = 1:100000
cam.ROI = roi;
img2 = snapshot(cam);
    [img_cam, img_edge] = lanedetection(img2, 80);
    subplot(2,2,2);
    image(img_cam);
    subplot(2,2,4);
    image(img_edge);
drawnow;
end