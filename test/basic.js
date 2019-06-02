describe('basic', function() {
  before(function() {
    this.timeout(60000);
    return new Promise((resolve) => {
      window.Module.onRuntimeInitialized = resolve;
    });
  });

  it('should have module functions', function() {
    const { expect } = window.chai;
    const { Mat, Resizer } = window.Module;
    expect(Mat).to.not.eql(undefined);
    expect(Resizer).to.not.eql(undefined);
  });

  it('should load the image', function() {
    const { imread } = window.Module;
    this.mat = imread('input-image');
  });

  it('should create the painter', function() {
    const { Resizer } = window.Module;
    this.resizer = new Resizer(this.mat);
  });

  it('should generate the palette', function() {
    const { expect } = window.chai;
    expect(this.resizer).to.have.property('run');
    this.resizer.run();
  });

  it('should destroy the matrix', function() {
    this.mat.delete();
  });
});
