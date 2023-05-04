
typedef enum {
  RECTANGULAR = 0,
  KAISER = 1,
  NUTTALL = 2,
  HANN = 3
} WINDOW_FUNCTION;

typedef struct {
  int speclen;
  WINDOW_FUNCTION wfunc;
  fftw_plan plan;

  double *time_domain;
  double *window;
  double *freq_domain;
  double *mag_spec;

  double data[];
} spectrum;

spectrum *create_spectrum(int speclen, WINDOW_FUNCTION window_function);

void destroy_spectrum(spectrum *spec);

double calc_magnitude_spectrum(spectrum *spec);
