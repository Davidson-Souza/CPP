/**
 * Calcula o mmc, com base no MDC e teoremas relacionados ao mesmo 
 * @Author: Derik
 * @Data: Sept, 2019
 */

int mmc(int a, int b){
    int mdc_res = mdc(a,b);
    return (a*b)/mdc_res;
}