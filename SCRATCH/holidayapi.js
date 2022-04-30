/**
 * @class       : holidayapi
 * @author      : alex (alex@T460)
 * @created     : sâmbătă apr 30, 2022 09:08:55 EEST
 * @description : holidayapi
 */



import { HolidayAPI } from 'holidayapi';
const key = 'b484e322-3aae-433d-b02f-9e8fed124cfd'
const holidayApi = new HolidayAPI({ key });
holidayApi.holidays({
  country: 'RO',
  year: '2021',
});
