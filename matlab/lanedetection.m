function [imgCam, imgEdge] = lanedetection(imgCam, threshold)

    % convert to grayscale
    imgGray = rgb2gray(imgCam);

    % create laplacian filter
    k = [1 2 1; 0 0 0; -1 -2 -1];
    % run sobel
    V = conv2(double(imgGray),k','same');
    
    % filter edges
    imgEdges = uint8((V > threshold) * 255);
    
    % coordinates of all detected objects
    [x, y] = find(imgEdges);
    
    % detect the center of all objects
    xCenter = round(mean(x));
    yCenter = round(mean(y));
    
    % create vector xx and yy for an area around the center of all objects
    xx = max(1, xCenter-2):min(xCenter+2, size(imgEdges, 1));
    yy = max(1, yCenter-2):min(yCenter+2, size(imgEdges, 2));
    
    % create new array with the size of "bw" and fill it with "0"
    bwdot = zeros(size(imgEdges), 'uint8');
    
    % if there is something detected at x and y...
    if ~isempty(x) && ~isempty(y)
        % ...mark the area around the center
        bwdot(xx, yy) = 255;
    % if nothing gets detected...
    else
        bwdot(xx, yy) = 0;
    end
    
    % add the marked area around the center to the array justRed
    imgEdge = imgEdges + bwdot;
end