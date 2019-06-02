var Module = window.Module = {};

Module['imread'] = function(imageSource) {
  const img = document.getElementById(imageSource);
  const canvas = document.createElement('canvas');
  canvas.width = img.width;
  canvas.height = img.height;
  const ctx = canvas.getContext('2d');
  ctx.drawImage(img, 0, 0, img.width, img.height);
  const imgData = ctx.getImageData(0, 0, canvas.width, canvas.height);
  return Module.matFromImageData(imgData);
};

Module['matFromImageData'] = function(imageData) {
  const mat = new Module.Mat(imageData.height, imageData.width, Module.CV_8UC4);
  mat.data.set(imageData.data);
  return mat;
};
